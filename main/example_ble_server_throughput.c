#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <DHT.h>

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b" // UUID del servicio que deseas anunciar
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8" // UUID de la característica dentro del servicio

#define DHTPIN 4     // Pin de datos del DHT11
#define DHTTYPE DHT11   // Tipo de sensor DHT

BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();

  // Crea un nuevo servidor BLE
  BLEDevice::init("ESP32");
  pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Añade una característica al servicio
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ |
                      BLECharacteristic::PROPERTY_WRITE
                    );

  // Asigna un valor inicial a la característica
  pCharacteristic->setValue("Hello World");
  
  // Inicia el servicio
  pService->start();

  // Anuncia el servicio
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();
  Serial.println("Servidor BLE iniciado");
}

void loop() {
  // Lectura de la temperatura y humedad del sensor DHT11
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Verifica si alguna lectura falló
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Error al leer el sensor DHT11");
    delay(2000);
    return;
  }

  // Convierte la temperatura a un string
  String temperatureString = String(temperature);

  // Muestra la temperatura en el puerto serie
  Serial.print("Temperatura: ");
  Serial.print(temperature);
  Serial.println(" °C");

  // Muestra la humedad en el puerto serie
  Serial.print("Humedad: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Espera hasta que se solicite la temperatura
  while (!pCharacteristic->written()) {
    delay(10);
  }

  // Verifica si se recibió el código hexadecimal correcto (0207e2103ef04)
  std::string receivedHex = pCharacteristic->getValue();
  if (receivedHex == "0207e2103ef04") {
    // Enviar la temperatura
    pCharacteristic->setValue(temperatureString.c_str());
    pCharacteristic->notify();
    Serial.println("Temperatura enviada por BLE");
  }

  delay(2000);
}
