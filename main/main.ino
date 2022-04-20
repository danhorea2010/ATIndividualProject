
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

template <typename T> T CLAMP(const T& value, const T& low, const T& high) 
{
  return value < low ? low : (value > high ? high : value); 
}

const int8_t SENSOR_PIN = A0;
//const int8_t SENSOR_PIN = 8;
const int8_t LED_OUTPUT = 10;
const int8_t BUTTON_RIGHT_PIN = 12;
const int8_t BUTTON_LEFT_PIN = 13;

const int16_t MAX_THRESHOLD = 590;
const int16_t MIN_THRESHOLD = 500;

int16_t currentThreshold = 572;

int button_right = 0;
int button_left = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_OUTPUT, OUTPUT);
  pinMode(SENSOR_PIN, INPUT_PULLUP);
  //pinMode(SENSOR_PIN, INPUT);

  // button
  pinMode(BUTTON_RIGHT_PIN, INPUT);
  pinMode(BUTTON_LEFT_PIN, INPUT);
  
  Serial.begin(9600);
}



void loop() {
  // put your main code here, to run repeatedly:
  int temp = analogRead(SENSOR_PIN);
  //int temp = digitalRead(SENSOR_PIN);
  button_right = digitalRead(BUTTON_RIGHT_PIN);
  button_left  = digitalRead(BUTTON_LEFT_PIN);
  
  Serial.print(F("Intensity="));
  Serial.print(temp);
  Serial.print(F("\n"));

  if (button_right == HIGH){
    currentThreshold = CLAMP<int16_t>(currentThreshold + 5,MIN_THRESHOLD,MAX_THRESHOLD );
  }
  if (button_left == HIGH){
    currentThreshold = CLAMP<int16_t>(currentThreshold - 5,MIN_THRESHOLD,MAX_THRESHOLD );
  }
  
  Serial.print(F("Current threshold:"));
  Serial.print(currentThreshold);
  Serial.print(F("\n"));
    
  if(temp >= currentThreshold){
    digitalWrite(LED_OUTPUT, HIGH);
    Serial.print(F("LED ON\n"));
  } else {
    digitalWrite(LED_OUTPUT, LOW);
     Serial.print(F("LED OFF\n"));
  }

  delay(350);

}
