
#include "MatrizLIL.h"
#include <assert.h>
#include <iomanip>
#include "helpers/Console.h"

MatrizLIL::MatrizLIL(const unsigned int filas, const unsigned int columnas) : Matriz(filas,columnas){
	std::vector< std::vector< std::tuple<int,float> > > datos;
}

MatrizLIL MatrizLIL::Identidad(unsigned int tam){
	MatrizLIL result(tam, tam);
	for (unsigned int i = 0; i < tam; i++){
		result.datos[i].push_back(std::make_tuple(i,1));
	}
	return result;
}

void MatrizLIL::Set(const unsigned int fil, const unsigned int col, float val){
	Matriz::CheckPosicionesValidas(fil,col);
	for(int i = 0; i<datos[fil].size();i++){
		if(std::get<0>(datos[fil][i]) == col){
			std::get<1>(datos[fil][i]) = val;
		} else { //supongo que viene ordenada y no había repetidos
			datos[fil].push_back(std::make_tuple(col,val));
			for (int j = datos[fil].size(); j>0; j-- ){ //ordena el valor nuevo
				if (std::get<0>(datos[fil][j]) < std::get<0>(datos[fil][j-1])){
					swap(datos[fil][j], datos[fil][j-1]);
				}
			}
		}
	}
}

float MatrizLIL::Get(const unsigned int fil, const unsigned int col) const {
	CheckPosicionesValidas(fil, col);
	int i = 0;
	while (std::get<0>(datos[fil][i]) != col){
		i++;
	}
	return std::get<1>(datos[fil][i]);
}

Matriz* MatrizLIL::Copiar() const {
	Matriz* copy = new MatrizLIL(*this);
	return copy;
}

void MatrizLIL::Sumar(const Matriz& m2){
	assert(GetCantidadColumnas() == m2.GetCantidadColumnas());
	assert(GetCantidadFilas() == m2.GetCantidadFilas());

	for (unsigned int i = 0; i < GetCantidadFilas(); i++){
		for (unsigned int j = 0; j < GetCantidadColumnas(); j++){
			Set(i, j, Get(i,j) + m2.Get(i,j));
		}
	}
}

void MatrizLIL::Restar(const Matriz& m2){
	assert(GetCantidadColumnas() == m2.GetCantidadColumnas());
	assert(GetCantidadFilas() == m2.GetCantidadFilas());

	for (unsigned int i = 0; i < GetCantidadFilas(); i++){
		for (unsigned int j = 0; j < GetCantidadColumnas(); j++){
			Set(i, j, Get(i,j) - m2.Get(i,j));
		}
	}
}

void MatrizLIL::Multiplicar(const Matriz& m2)
{
	assert(GetCantidadColumnas() == m2.GetCantidadFilas());

	for (unsigned int i = 0; i < GetCantidadFilas(); i++){
		if (datos[i].size() > 0){ //recorro filas de MatrizLIL, si es nula la ignoro
			for (unsigned int j = 0; j < m2.GetCantidadColumnas(); j++){ // recorro las columnas donde voy a calcular el valor
				float accum = 0;
				for (unsigned int k = 0; k < datos[i].size(); k++){
					accum += std::get<1>(datos[i][k]) * m2.Get(std::get<0>(datos[i][k]), j); //fila * columna
					Set(i,j, accum);
				}
			}
		}
	}
}

void MatrizLIL::Multiplicar(const float& f){
	for (unsigned int i = 0; i < GetCantidadFilas(); i++){
		for (unsigned int j = 0; j < datos[i].size(); j++){
			std::get<1>(datos[i][j]) *= f;
		}
	}
}

void MatrizLIL::Extender(const Vector& v){
	assert(v.GetTamano() == GetCantidadFilas());
	SetTamano(GetCantidadFilas(), GetCantidadColumnas()+1);

	for (unsigned int i = 0; i < v.GetTamano(); i++){
		Set(i, GetCantidadColumnas()-1, v.Get(i));
	}
}

void MatrizLIL::Escalonar(){
	if(EstaEscalonada())
	{
		return;
	}

	// Eliminacion Gaussiana
	unsigned int currentCol = 0;

	for(unsigned int currentFil = 0; currentFil < GetCantidadFilas() && currentCol < GetCantidadColumnas() - 1; currentFil++)
	{
		for(unsigned int fil = currentFil+1; fil < GetCantidadFilas(); fil++)
		{
			float srcVal = (Get(currentFil, currentCol));
			float dstVal = -(Get(fil, currentCol));

			float escalar = dstVal / srcVal;
			GaussSumarMultiplo(currentFil, fil, escalar, currentFil);

			//Console::Debug() << "F" << fil << "=" << "F" << currentFil << " x " << escalar << " + " << "F" << fil << std::endl;  // @suppress("Invalid overload")
			//Console::Debug() << m << std::endl;  // @suppress("Invalid overload")
		}

		currentCol++;
	}
}

void MatrizLIL::GaussMultiplicarFila(unsigned int fila, float escalar)
{
	for(unsigned int col = 0; col < this->GetCantidadColumnas(); col++)
	{
		this->Set(fila, col, this->Get(fila, col) * escalar);
	}
}

void MatrizLIL::GaussSumarMultiplo(unsigned int filaSrc, unsigned int filaDst, float escalar, unsigned int offset)
{
	//assert(filaSrc < this->GetCantidadFilas());
	//assert(filaDst < this->GetCantidadFilas());

	for(unsigned int col = offset; col < this->GetCantidadColumnas(); col++)
	{
		float srcVal = this->Get(filaSrc, col);
		float dstval = this->Get(filaDst, col);
		float result = dstval + srcVal * escalar;
		this->Set(filaDst, col, result);
	}
}

void MatrizLIL::SetTamano(const unsigned int filas, const unsigned int columnas)
{
	Matriz::SetTamano(filas, columnas);
}



MatrizLIL::~MatrizLIL(){
}
