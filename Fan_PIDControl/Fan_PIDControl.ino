//PID configuration
double cp = 1;
double ci = 0;
double cd = 0.1;

//Temperature measurement variables
const float R2 = 100000;    // Resistance at T0 (in Ohm)
const float R0 = (1023/510 - 1)*R2;   //R1 at T0
const float B = 4600;       // B-value in [4250K, 4299K]
const float T0 = 298.15;    // Room temperature 25°C
float V_meas;
double T;
float R;

// Variables used for PID control function
double dt;
double now;
double prev;
double error;
double lasterr;
double in, out;
double integral, derivative;
double T_eq;
int duty;

void setup() {
  Serial.begin(9600);
  pinMode(11, OUTPUT);
  pinMode(2, INPUT);
  T_eq = 300;         // Equilibrium temperature we want to achieve

}

void loop() {
  // Temp calculation (using eqs 8 and 9 from Manual)
  V_meas = analogRead(0);
  R = (1023 / V_meas - 1) * R0;
  T = 1 / (log(R / R0) / B + 1 / T0);

  // Print current T to Serial
  //Serial.println(T);

  // Get PID output
  out = PID(T);
  Serial.println(T);
  out *= 100;
  duty = map(out, 0, 100, 0, 255);
  analogWrite(11, duty);
  delay(100);
}

double PID(double T) {
  now = millis();
  dt = (double)(now - prev);

  error = T - T_eq;                           // error term
  integral += error * dt / 1000;              // integral term
  derivative = (error - lasterr) * 1000 / dt; // derivative term

  // Calculate output
  double out = cp * error + ci * integral + cd * derivative;

  // Store current values of error and time
  lasterr = error;
  prev = now;

  // Set 0, 1 as min/max of PID
  if (out >= 1) {
    out = 1;
  }
  if (out <= 0) {
    out = 0;
  }

  return out;
}
