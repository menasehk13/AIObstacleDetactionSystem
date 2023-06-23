#include <WebServer.h>
#include <Wifi.h>
#include <esp32cam.h>
#include <TensorFlowLite.h>

const char* model = "/sdcard/model.tflite";
const char* WIFI_SSID = "test";
const char* WIFI_PASS = "12345678";

webServer server(80);

// put  the motor controlls pins


TfLiteModel* tfliteModel;
TfLiteInterpreter* interpreter;

const int imgWidth = 224;
const int imgHeight = 224;
const int imgChannels = 1;

void setup(){

// initialize the ESP32 cam

  tfliteModel = tflite::GetModelFromSD(model);
  interpreter = new TfLiteInterpreter(tfliteModel);
  interpreter->Invoke();



  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
}

void detectObstacle(){
   // Capture image from ESP32-CAM
  camera_fb_t* fb = esp_camera_fb_get();
  if (!fb) {
    Serial.println("Failed to capture image");
    return;
  }

  // Convert the captured image to grayscale
  Image image = Image(fb->width, fb->height, imgChannels);
  for (int y = 0; y < fb->height; y++) {
    for (int x = 0; x < fb->width; x++) {
      uint8_t pixelValue = fb->buf[y * fb->width + x];
      image.setPixel(x, y, pixelValue);
    }
  }

  // Normalize the image pixel values
  image.normalize(0, 255);

  // Resize the image to match the input size expected by the model
  Image resizedImage = image.resize(imgWidth, imgHeight);

  float* inputBuffer = interpreter->input(0)->data.f;
  for (int y = 0; y < imgHeight; y++) {
    for (int x = 0; x < imgWidth; x++) {
      float pixelValue = resizedImage.getPixel(x, y);
      inputBuffer[y * imgWidth + x] = pixelValue;
    }
  }

  // Run inference
  interpreter->Invoke();

  // Access the inference result
  float inferenceResult = interpreter->output(0)->data.f[0];

  // Determine obstacle presence based on the inference result
  bool obstacleDetected = (inferenceResult > 0.5);

  if (obstacleDetected)
  {
    // change the direction of the motors
    /* code */
  }

    esp_camera_fb_return(fb);
  
}

void loop() {
  unsigned long currentTime = millis();
  static unsigned long previousTime = 0;
  
  // Capture image and detect obstacle at specified interval
  if (currentTime - previousTime >= streamInterval) {
    detectObstacle();
    previousTime = currentTime;
  }
}