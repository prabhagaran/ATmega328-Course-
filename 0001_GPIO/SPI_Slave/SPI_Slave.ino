

void SPI_SlaveInit() {
    // Set MISO as output
    DDRB |= (1 << DDB4);

    // Enable SPI
    SPCR |= (1 << SPE)|(1 << DORD)|(1 << CPHA);
}

uint8_t SPI_SlaveReceive() {
    // Wait for reception complete
    while (!(SPSR & (1 << SPIF)));

    // Return received data
    return SPDR;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SPI_SlaveInit();

}

void loop() {
  // put your main code here, to run repeatedly:
  char receivedData = SPI_SlaveReceive();

        // Process the received data as needed
        // ...
   Serial.println(receivedData);
        _delay_ms(1000); 

}
