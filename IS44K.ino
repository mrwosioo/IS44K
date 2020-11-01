#define trigPin 13
#define echoPin 12   /*przypisujemy uzywanym przez nas pin'om konkretne nazwy, aby calosc byla bardziej przejrzysta*/
#define enablePin1 11
#define enablePin2 8
#define in1A  4
#define in2A  7 
#define in3A  6
#define in4A  5

void setup()
{
  pinMode(trigPin , OUTPUT);
  pinMode(echoPin , INPUT);
  pinMode(enablePin1 , OUTPUT);
  pinMode(in1A , OUTPUT);
  pinMode(in2A , OUTPUT);
  pinMode(enablePin2 , OUTPUT);
  pinMode(in3A , OUTPUT);
  pinMode(in4A , OUTPUT);
  digitalWrite(enablePin1 , LOW);
  digitalWrite(enablePin2 , LOW);     
  Serial.begin(9600);
   /*
   * w funkcji setup okreslamy ktorych pinow bedziemy uzywac jako wejscie i wyjscie,        
   * okreslamy iz bedziemy korzystac z portu szeregowego, aby moc na PC odczytywac dane (predkosc przesylu 9600 bit/s)
   */
   delay(5000);
}


float measure_distance() /*funkcja odpowiada za mierzenie odleglosci w cm za pomoca czujnika hc-sr04*/
{
   float Time , distance;  
   /*
   * definiujemy zmienne calkowite,  gdzie time1 to czas w jakim sygnal wraca do czujnika odbity od przeszkody
   * distance do dystans czujnika od przeszkody
   */
  digitalWrite(trigPin , HIGH);
  delayMicroseconds(10);      /*ustawiamy wysokie napiecie na pin'ie trig i po 10 us ustawiamy na nim niskie napiecie, czujnik dokonuje pomiaru*/
  digitalWrite(trigPin , LOW);
 
  Time = pulseIn(echoPin , HIGH);
   /*
   * do zmiennej time1 funkcja pulseIn() przypisuje czas jaki uplynie od momentu gdy pin echo przelaczy sie na wysokie napiecie
   * do momentu az przelaczy sie na niskie, jest to czas w jakim dzwiek pokonuje odleglosc od czujnika do przeszkody
   */
  distance = Time / 58; /*czas ten dzielimy przez 58us, bo w tym czasie dzwiek pokonuje odleglosc 1cm */

  return distance;
}
/*Ponizsze funkcje wykonuja to na co wskazuje ich nazwa*/
void RunLeftMotor()
{
  digitalWrite(in1A , HIGH);
  digitalWrite(in2A , LOW);      /*ustawienia pinow zgodne z tabela logiczna dla ukladu l293d*/
  digitalWrite(enablePin1 , HIGH); 
}

void StopLeftMotor()
{
  digitalWrite(in1A , LOW);
  digitalWrite(in2A , LOW);
  digitalWrite(enablePin1 , LOW);
}

void RunRightMotor()
{
  digitalWrite(in3A , HIGH);
  digitalWrite(in4A , LOW);
  digitalWrite(enablePin2 , HIGH);
  
}

void StopRightMotor()
{
  digitalWrite(in3A , LOW);
  digitalWrite(in4A , LOW);
  digitalWrite(enablePin2 , LOW);
}

void RunBoth()
{
  RunRightMotor();
  RunLeftMotor();
}

void Turn()
{
  digitalWrite(in3A , HIGH);
  digitalWrite(in4A , LOW);
  digitalWrite(enablePin2 , HIGH);
  digitalWrite(in1A , LOW);
  digitalWrite(in2A , HIGH);
  digitalWrite(enablePin1 , HIGH);
}

void StopBoth()
{
  StopRightMotor();
  StopLeftMotor();
}

void loop()
{
  if(measure_distance()<35)
  {
    Turn();
    delay(50);
    StopBoth();       //Gdy odleglosc przedmiotu od czujnika jest mniejsza od 40cm robot skreca
    delay(10);
  }
  else
  {
    RunBoth();
    delay(50);
    StopBoth();      //Gdy odleglosc przedmiotu od czujnika jest wieksza od 40cm robot jedzie prosto
    delay(10);
    }
}

