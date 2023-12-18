#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

float VitezaX (float VX, float w, float f, float t)
{
	return VX*sin(w*t+f);
}

float VitezaY (float VX, float w, float f, float t, float m, float q, float B, float E)
{
	return (m*w*VX/(q*B)*cos(w*t+f))-E/B;
}

float VitezaZ (float v0z)
{
	return v0z;
}

float Viteza (float vx, float vy, float vz)
{
		return sqrt(vx*vx+vy*vy+vz*vz);
}


float CoordX(float VX,float w,float f,float t)
{
	return (-VX/w)*cos(w*t+f)+VX*cos(f)/w;
}

float CoordY(float VX,float w,float f,float t,float m,float q,float B,float E)
{
	return (m*VX/(q*B)*sin(w*t+f))-E*t/B-m*VX/(q*B);
}

float CoordZ(float v0z, float t)
{
	return v0z*t;
}

float distanta (float x, float y, float z)
{
	return sqrt (x*x+y*y+z*z);
}
float AcceleratieX (float VX, float w, float f, float t)
{
	return w*VX*cos(w*t+f);
}

float AcceleratieY (float VX, float w, float f, float t, float m,float q, float B)
{
	return -(m*w*w*VX/(q*B))*sin(w*t+f);
}

float Acceleratie (float ax, float ay)
{
		return sqrt(ax*ax+ay*ay);
}

int main()
{
ofstream FisCoord;
FisCoord.open("FisCoord.txt");
ofstream FisVit;
FisVit.open("FisVit.txt");
ofstream FisAcc;
FisAcc.open("FisAcc.txt");

float v0x, v0y, v0z, ax, ay, az,Acc, vx, vy, vz, v, x, y, z, d, q;
float E, B, m;
cout<<"Toate unitatile trebuie trecute in SI"<<endl;
cout<<"coordonatele initiale vor fi (0,0,0)"<<endl;
//introducem datele initiale:
cout<<"Introduceti componentele vitezei initiale in urmatoare ordine: v0x, v0y, v0z"<<endl;
cin>>v0x;
cin>>v0y;
cin>>v0z;
cout<<"E va avea componenta doar pe axa Ox, introduceti valoarea lui E (pozitiva sau negativa):"<<endl;
cin>>E;
cout<<"B va avea componenta doar pe axa Oz, introduceti valoarea lui B(pozitiva sau negativa)"<<endl;
cin>>B;
cout<<"Introduceti masa"<<endl;
cin>>m;
cout<<"Introduceti sarcina electrica (pozitiva sau negativa !NENULA!)"<<endl;
cin>>q;

//timpul:
float t;
//incrementul de timp
float dt;
//timpul maxim (pana la care opereaza programul)
float Tmax;

//inregistrare timp
cout<<"Introduceti timpul dupa care se opreste programul (timpul maxim)"<<endl;
cin>>Tmax;
cout<<"Introduceti incrementul de timp (dt-intervalul de timp dintre 2 masuratori) "<<endl;
cin>>dt;


if (B==0)
{
		for(t=0; t<Tmax; t=t+dt)
		{
			vx=v0x+q*E*t/m;
			vy=v0y;
			vz=v0z;
			v=Viteza (vx, vy, vz);

			x=v0x*t+q*E*t*t/(2*m);
			y=t*v0y;
			z=t*v0z;
			d=distanta(x, y, z);

			ax=q*E/m;
			ay=0;
			az=0;
			Acc=ax;

			FisCoord<<t<<" "<<d<<" "<<x<<" "<<y<<" "<<z<<endl;
			FisVit<<t<<" "<<v<<" "<<vx<<" "<<vy<<" "<<vz<<endl;
			FisAcc<<t<<" "<<Acc<<" "<<ax<<" "<<ay<<" "<<az<<endl;
		}

}
else
{
//pulsatia:
float w;
w=abs(q*B/m);

//variabile pentru calculul lui VX:

float a,b;
a=pow(q*B*v0y/(m*w)+q*E,2);
b=pow(v0x,2);

float VX;
VX= sqrt (a+b);

//faza initiala:
float f;
f=asin(v0x/VX);

//extragere date program

for(t=0; t<Tmax; t=t+dt)
{

	vx= VitezaX(VX, w, f, t);
	vy= VitezaY(VX, w, f, t, m, q, B, E);
	vz= VitezaZ(v0z);
	v=Viteza(vx, vy, vz);

	x= CoordX(VX, w, f, t);
	y= CoordY(VX, w, f, t, m, q, B, E);
	z= CoordZ(v0z, t);
	d= distanta(x, y, z);

	ax= AcceleratieX(VX, w, f, t);
	ay= AcceleratieY(VX, w, f, t, m, q, B);
	az=0;
	Acc=Acceleratie(ax, ay);
/*
	cout<<"Componenta pe Ox a vitezei este:"<<vx<<endl;
	cout<<"Componenta pe Oy a vitezei este:"<<vy<<endl;
	cout<<"Componenta pe Oz a vitezei este:"<<vz<<endl;

	cout<<"Coordonata pe Ox este:"<<x<<endl;
	cout<<"Coordonata pe Oy este:"<<y<<endl;
	cout<<"Coordonata pe Oz este:"<<z<<endl;

	cout<<"Distanta fata de origine este:"<<d<<endl;

	cout<<"Componenta pe Ox a acceleratiei este:"<<ax<<endl;
	cout<<"Componenta pe Oy a acceleratiei este:"<<ay<<endl;
	cout<<"Componenta pe Oz a acceleratiei este:"<<az<<endl;
*/

FisCoord<<t<<" "<<d<<" "<<x<<" "<<y<<" "<<z<<endl;
FisVit<<t<<" "<<v<<" "<<vx<<" "<<vy<<" "<<vz<<endl;
FisAcc<<t<<" "<<Acc<<" "<<ax<<" "<<ay<<" "<<az<<endl;

}
}
cout<<"A fost generat un fisier cu numele FisCoord.txt in care sunt trecute pe coloane urmatoarele:"<<endl;
cout<<"Coloana 1: timpul"<<endl;
cout<<"Coloana 2: distanta pana la origine"<<endl;
cout<<"Coloana 3: coordonata x"<<endl;
cout<<"Coloana 4: coordonata y"<<endl;
cout<<"Coloana 5: coordonata z"<<endl;
cout<<"Pentru generarea graficelor se utilizeaza gnuplot, urmand a fi utilizata sintagma:"<<endl;
cout<<"plot \"FisCoord.txt\" using i:j"<<endl;
cout<<"In loc de i si j se precizeaza numarul coloanei a carei variabila se doreste a fi reprezentata"<<endl;
cout<<endl;
cout<<"A fost generat un fisier cu numele FisVit.txt in care sunt trecute pe coloane urmatoarele:"<<endl;
cout<<"Coloana 1: timpul"<<endl;
cout<<"Coloana 2: viteza totala (in modul)"<<endl;
cout<<"Coloana 3: viteza pe Ox"<<endl;
cout<<"Coloana 4: viteza pe Oy"<<endl;
cout<<"Coloana 5: viteza pe Oz"<<endl;
cout<<"Pentru generarea graficelor se utilizeaza gnuplot, urmand a fi utilizata sintagma:"<<endl;
cout<<"plot \"FisVit.txt\" using i:j"<<endl;
cout<<"In loc de i si j se precizeaza numarul coloanei a carei variabila se doreste a fi reprezentata"<<endl;
cout<<endl;
cout<<"A fost generat un fisier cu numele FisAcc.txt in care sunt trecute pe coloane urmatoarele:"<<endl;
cout<<"Coloana 1: timpul"<<endl;
cout<<"Coloana 2: acceleratia totala (in modul)"<<endl;
cout<<"Coloana 3: acceleratia pe Ox"<<endl;
cout<<"Coloana 4: acceleratia pe Oy"<<endl;
cout<<"Coloana 5: acceleratia pe Oz"<<endl;
cout<<"Pentru generarea graficelor se utilizeaza gnuplot, urmand a fi utilizata sintagma:"<<endl;
cout<<"plot \"FisAcc.txt\" using i:j"<<endl;
cout<<"In loc de i si j se precizeaza numarul coloanei a carei variabila se doreste a fi reprezentata"<<endl;
cout<<"Pentru generarea graficelor 3D se utilizeaza urmatoarea sintagma:"<<endl;
cout<<"splot \"NumeFisier\" using i:j:k with lines"<<endl;


FisCoord.close();
FisVit.close();
FisAcc.close();


return 0;
}
