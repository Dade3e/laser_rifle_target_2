Progetto laser targhet,

In questa seconda versione uso un pannello solare per vedere quando impatta collegato al pin Ain3, e potenziometro per la soglia nel pin Ain2

//                  +-\/-+
// Ain0 (D 5) PB5  1|    |8  Vcc
// Ain3 (D 3) PB3  2|    |7  PB2 (D 2) Ain1
// Ain2 (D 4) PB4  3|    |6  PB1 (D 1) pwm1
//            GND  4|    |5  PB0 (D 0) pwm0   -> gong
//                  +----+


Quando colpisci il pin D0 è connesso ad un 2N2222 collegato ad un solenoide per suonare un campanello
