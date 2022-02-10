/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

/*
 *  KisiTespiti örneği,
 *  TensorFlowLite yapay zeka kütüphanesinin kullanıldığı bu örnekte 
 *  Kamera görüntüleri seri terminalde çizdirmektedir.
 *  
 *  Deneyap Mini Kartın kamera bağlantısı olmadığı için bu örnek Deneyap Mini Kartını desteklememektedir.
 * 
 */
#include <TensorFlowLite_ESP32.h>

#include "main_functions.h"
#include "detection_responder.h"
#include "image_provider.h"
#include "model_settings.h"
#include "person_detect_model_data.h"
#include "tensorflow/lite/experimental/micro/kernels/micro_ops.h"
#include "tensorflow/lite/experimental/micro/micro_error_reporter.h"
#include "tensorflow/lite/experimental/micro/micro_interpreter.h"
#include "tensorflow/lite/experimental/micro/micro_mutable_op_resolver.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/version.h"

namespace {
tflite::ErrorReporter* error_reporter = nullptr;
const tflite::Model* model = nullptr;
tflite::MicroInterpreter* interpreter = nullptr;
TfLiteTensor* input = nullptr;

// Giriş, çıkış ve ara diziler için kullanılacak bir bellek alanı
constexpr int kTensorArenaSize = 70 * 1024;
static uint8_t tensor_arena[kTensorArenaSize];
}  // namespace

// Arduino uyumluluğu için bu fonksiyonun ismi önemlidir.
void setup() {
  // Set up logging. Google style is to avoid globals or statics because of
  // lifetime uncertainty, but since this has a trivial destructor it's okay.
  // NOLINTNEXTLINE(çalışma zamanı-global-değişkenler)
  static tflite::MicroErrorReporter micro_error_reporter;
  error_reporter = &micro_error_reporter;

  // Modeli kullanılabilir bir veri yapısına eşleyin. Bu herhangi bir şey içermiyor.
  // kopyalama veya ayrıştırma, çok hafif bir işlemdir
  model = tflite::GetModel(g_person_detect_model_data);
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    error_reporter->Report(
        "Sağlanan model şema sürümü %d eşit değil"
        "desteklenen sürüm %d.",
        model->version(), TFLITE_SCHEMA_VERSION);
    return;
  }

  // Yalnızca ihtiyacımız olan işlem uygulamalarını içeri çekin
  // Bu grafiğin ihtiyaç duyduğu tüm işlemlerin tüm listesine dayanır
  // AllOpsResolver'ı kullanmak daha kolay bir yaklaşımdır, ancak bu
  // olmayan op uygulamaları için kod alanında bazı cezalara maruz kalır
  // bu grafik tarafında gerekli
  // tflite::ops::micro::AllOpsResolver çözümleyici;
  // NOLINTNEXTLINE(çalışma zamanı-global-değişkenler)
  static tflite::MicroMutableOpResolver micro_mutable_op_resolver;
  micro_mutable_op_resolver.AddBuiltin(
      tflite::BuiltinOperator_DEPTHWISE_CONV_2D,
      tflite::ops::micro::Register_DEPTHWISE_CONV_2D());
  micro_mutable_op_resolver.AddBuiltin(tflite::BuiltinOperator_CONV_2D,
                                       tflite::ops::micro::Register_CONV_2D());
  micro_mutable_op_resolver.AddBuiltin(
      tflite::BuiltinOperator_AVERAGE_POOL_2D,
      tflite::ops::micro::Register_AVERAGE_POOL_2D());

  // Modeli çalıştırmak için bir yorumlayıcı oluşturun
  static tflite::MicroInterpreter static_interpreter(
      model, micro_mutable_op_resolver, tensor_arena, kTensorArenaSize,
      error_reporter);
  interpreter = &static_interpreter;

  // Modelin tensörleri için tensor_arena'dan bellek ayırın
  TfLiteStatus allocate_status = interpreter->AllocateTensors();
  if (allocate_status != kTfLiteOk) {
    error_reporter->Report("AllocateTensors() hatası");
    return;
  }

  // Modelin girişi için kullanılacak bellek alanı hakkında bilgi alın
  input = interpreter->input(0);
}

// Arduino uyumluluğu için bu fonksiyon önemlidir
void loop() {
  // Kameradan görüntü alın
  if (kTfLiteOk != GetImage(error_reporter, kNumCols, kNumRows, kNumChannels,
                            input->data.uint8)) {
    error_reporter->Report("Görüntü yakalama başarısız oldu");
  }

  // Modeli bu girdi üzerinde çalıştırın ve başarılı olduğundan emin olun
  if (kTfLiteOk != interpreter->Invoke()) {
    error_reporter->Report("Çağrı başarısız");
  }

  TfLiteTensor* output = interpreter->output(0);

  // Çıkarım sonuçlarını işleyin
  uint8_t person_score = output->data.uint8[kPersonIndex];
  uint8_t no_person_score = output->data.uint8[kNotAPersonIndex];
  RespondToDetection(error_reporter, person_score, no_person_score);
}
