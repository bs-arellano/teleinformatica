# Configuración de Thingsboard
1. Crear una cuenta en [Thingsnboard](https://demo.thingsboard.io/).
2. Crear un nuevo [dispositivo](https://demo.thingsboard.io/entities/devices) y obtener su token.
3. Crear un nuevo [dashboard](https://demo.thingsboard.io/dashboards) y agregar widgets.
    - El estado del switch depende de la timeseries `buttonState`
    - El led puede ser controlado con el metodo RPC `setLedSwitchValue`
# Instalación en el ESP32
1. Descargar el [IDE de Arduino](https://www.arduino.cc/en/software).
2. Agregar las placas ESP32 al IDE.
    Archivo > Preferencias > Gestor de tarjetas adicionales
    ```
    https://dl.espressif.com/dl/package_esp32_index.json
    ```
3. Elegir la placa y puerto correspondiente. Por ejemplo "ESP32-CAM" y "COM-3".
4. Agregar la librería "Thingsboads" y sus dependencias. La documentación de la librería se encuantra en el siguiente enlace: 
    - [Arduino Reference](https://www.arduino.cc/reference/en/libraries/thingsboard/)
    - [Github](https://github.com/thingsboard/thingsboard-client-sdk)
5. Cargar el archivo [thingsboard.ino](https://github.com/bs-arellano/teleinformatica/blob/main/ThingsBoard/thingsboard.ino), remplazando credenciales WIFI y el token de acceso a [Thingsnboard](https://demo.thingsboard.io/).
6. Compilar, subir y revisar la consola serial (9600). La salida esperada debería ser:
    ```
    Wifi connected!
    Connected to TB server
    Subscribed to RPC
    ```