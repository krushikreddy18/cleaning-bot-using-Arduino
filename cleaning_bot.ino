#define IN1 3
#define IN2 5
#define IN3 2
#define IN4 4
#define TRIG_PIN 9 // Ultrasonic sensor trigger pin
#define ECHO_PIN 10 // Ultrasonic sensor echo pin
#define MAX_DISTANCE 35 // Maximum distance to detect obstacles (in centimeters)
char path[100]; // Array to store the path
int pathIndex = 0; // Index to keep track of the path
bool automaticMode = false; // Flag to indicate automatic mode
bool stopRequested = false; // Flag to indicate stop request
char stop;
char value;
void setup() {
Serial.begin(9600);
pinMode(IN1, OUTPUT);
pinMode(IN2, OUTPUT);
pinMode(IN3, OUTPUT);
pinMode(IN4, OUTPUT);
pinMode(TRIG_PIN, OUTPUT);
pinMode(ECHO_PIN, INPUT);
}
void loop() {
if (Serial.available() > 0) {
value = Serial.read();
Serial.println(value);
if (value == 'F' && !automaticMode) {
Forward();
delay(500);
Stop();
storePath('F'); // Store the command
} else if (value == 'B' && !automaticMode) {
Backward();
delay(500);
Stop();
storePath('B');
} else if (value == '0' && !automaticMode) {
Stop();
storePath('0');
} else if(value == 'L' && !automaticMode){
Left();
delay(200);
Stop();
storePath('L');
} else if(value == 'R' && !automaticMode){
Right();
delay(200);
Stop();
storePath('R');
} else if (value == 'X' && !automaticMode) {
// Follow the reverse path to return to the original position
followReversePath();
} else if (value == 'T') {
// Enter automatic mode
automaticMode = true;
} else if (value == 'S') {
// Enter manual mode
automaticMode = false;
}
}
while (automaticMode) {
if (Serial.available() > 0)
{
stop = Serial.read();
Serial.println(stop);
}
// If in automatic mode and not stop requested, perform obstacle avoidance
if (stop!='P')
{
dodgeObstacle();
}
else
Stop();
}
}
void storePath(char command) {
path[pathIndex++] = command; // Store the command in the path array
}
void followReversePath() {
for (int i = pathIndex - 1; i >= 0; i--) {
// Follow the reverse of the stored path
char command = path[i];
switch (command) {
case 'F':
{
Backward();
delay(500);
Stop();
}
break;
case 'B':
{
Forward();
delay(500);
Stop();
}
break;
case 'L':
{
Right();
delay(200);
Stop();
}
break;
case 'R':
{
Left();
delay(200);
Stop();
}
break;
case '0':
Stop(); // No need to move, just stop
break;
default:
// Invalid command
break;
}
delay(500); // Adjust delay as per your requirement
}
}
void dodgeObstacle() {
long duration, distance;
digitalWrite(TRIG_PIN, LOW);
delayMicroseconds(2);
digitalWrite(TRIG_PIN, HIGH);
delayMicroseconds(10);
digitalWrite(TRIG_PIN, LOW);
duration = pulseIn(ECHO_PIN, HIGH);
distance = duration * 0.034 / 2;
Serial.print("Distance: ");
Serial.print(distance);
Serial.println(" cm");
if (distance < MAX_DISTANCE && distance>0) {
// Obstacle detected, dodge it
// Reverse for a second
Forward();
delay(1000);
Left(); // Turn left
delay(500);
Backward();
delay(1000);
Right();
delay(500);
// Adjust the delay according to your robot's speed and turning radius
stopRequested = true; // Set stop requested flag
} else {
// No obstacle, continue forward
Backward();
stopRequested = false; // Reset stop requested flag
}
}
void Forward() {
digitalWrite(IN1, HIGH);
digitalWrite(IN2, LOW);
digitalWrite(IN3, HIGH);
digitalWrite(IN4, LOW);
}
void Backward() {
digitalWrite(IN1, LOW);
digitalWrite(IN2, HIGH);
digitalWrite(IN3, LOW);
digitalWrite(IN4, HIGH);
}
void Stop() {
digitalWrite(IN1, LOW);
digitalWrite(IN2, LOW);
digitalWrite(IN3, LOW);
digitalWrite(IN4, LOW);
}
void Left() {
digitalWrite(IN1, HIGH);
digitalWrite(IN2, LOW);
digitalWrite(IN3, LOW);
digitalWrite(IN4, HIGH);
}
void Right() {
digitalWrite(IN1, LOW);
digitalWrite(IN2, HIGH);
digitalWrite(IN3, HIGH);
digitalWrite(IN4, LOW);
}