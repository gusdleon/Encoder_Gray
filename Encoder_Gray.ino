//Matriz con el orden de los pasos
int steps[4][4] = {
  {1, 0, 0, 1},
  {0, 0, 1, 1},
  {0, 1, 1, 0},
  {1, 1, 0, 0}
};

int pos[4]; //Matriz con la posicion de el encoder
String poc="0000";  //String con la posicion de el encoder
int margen = 100; //Margen de sensado
int espera = 2; //Tiempo entre pasos
String inputString = "";  //String que guarda los datos enviados
String entrada ="0000";
bool stringComplete = false; //cuando el string esta completo
bool rotacion = false;

void setup() {
  delay(3*1000);
  Serial.begin(250000);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  Serial.println("Introduce una direcion en codigo Gray 1 o 0 en el formato xxxx");
  inputString.reserve(200); //reserva 200 bytes para el string de entrada
}

void loop() {
  posicion();
  Serial.print("Posicion a mantener: ");
  Serial.print(entrada);
  Serial.print(" -> ");
  Serial.print("Posicion actual: ");
  Serial.print(poc);
  Serial.print("\t || \t");  

  Serial.print("Valores analogicos de los sensores: G1= ");
  Serial.print(analogRead(A0));
  Serial.print("=");
  Serial.print(pos[0]);
  Serial.print("\t| G2= ");
  Serial.print(analogRead(A1));
  Serial.print("=");
  Serial.print(pos[1]);
  Serial.print("\t| G3= ");
  Serial.print(analogRead(A2));
  Serial.print("=");
  Serial.print(pos[2]);
  Serial.print("\t| G4= ");
  Serial.print(analogRead(A3));
  Serial.print("=");
  Serial.println(pos[3]);
  
  //Rotacion
  if (rotacion) {
    digitalWrite(8, steps[0][0]);
    digitalWrite(9, steps[0][1]);
    digitalWrite(10, steps[0][2]);
    digitalWrite(11, steps[0][3]);
    delay(espera);
    digitalWrite(8, steps[1][0]);
    digitalWrite(9, steps[1][1]);
    digitalWrite(10, steps[1][2]);
    digitalWrite(11, steps[1][3]);
    delay(espera);
    digitalWrite(8, steps[2][0]);
    digitalWrite(9, steps[2][1]);
    digitalWrite(10, steps[2][2]);
    digitalWrite(11, steps[2][3]);
    delay(espera);
    digitalWrite(8, steps[3][0]);
    digitalWrite(9, steps[3][1]);
    digitalWrite(10, steps[3][2]);
    digitalWrite(11, steps[3][3]);
    delay(espera);
  }

  if (stringComplete) {
    Serial.println(inputString);
    //clearthestring:
    inputString = "";
    stringComplete = false;
  }

  if (entrada != poc){
      rotacion= true;
    }else{
      rotacion=false;
    }
}

//Captura de posicion
void posicion() {
  pos[0] = analogRead(A3);
  if (pos[0] > margen) {
    pos[0] = 1;
  } else {
    pos[0] = 0;
  } pos[1] = analogRead(A2);
  if (pos[1] > margen) {
    pos[1] = 1;
  } else {
    pos[1] = 0;
  } pos[2] = analogRead(A1);
  if (pos[2] > margen) {
    pos[2] = 1;
  } else {
    pos[2] = 0;
  } pos[3] = analogRead(A0);
  if (pos[3] > margen) {
    pos[3] = 1;
  } else {
    pos[3] = 0;
  }
  poc="";
  for(int k=0; k<4; k++){
    poc += pos[k];
  }
}

//Entrada de datos
void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();  //recibe el byte nuevo
    if (inChar == '\n') {
      stringComplete = true;
      entrada=inputString;
      return;
    }
    inputString += inChar;//agregandolo a el string de entrada
    //Si el caracter es uno de nueva linea, activa una vandera para que el loop principal pueda
    //hacer algo con los datos recibidos
  }
}
