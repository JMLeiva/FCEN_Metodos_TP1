
#include "MatrizLIL.h"
#include <assert.h>
#include <iomanip>
#include "helpers/Console.h"

MatrizLIL::MatrizLIL(const unsigned int filas, const unsigned int columnas) : Matriz(filas,columnas){
	std::vector< std::vector< std::tuple<int,float> > > datos;
}

void MatrizLIL::Set(const unsigned int fil, const unsigned int col, float val){
	Matriz::CheckPosicionesValidas(fil,col);
	for(int i = 0; i<datos[fil].size();i++){
		if(get<0>(datos[fil][i]) == col){
			get<1>(datos[fil][i]) = val;
		} else { //supongo que viene ordenada y no había repetidos
			datos[fil.push_back(std::make_tuple(col,val));
			for (int j = datos[fil].size(); j>0; j-- ){ //ordena el valor nuevo
				if (get<0>(datos[fil][j]) < get<0>(datos[fil][j-1])){
					swap(datos[fil][j], datos[fil][j-1]);
				}
			}
		}
	}
}

float MatrizLIL::Get(const unsigned int fil, const unsigned int col) const {
	CheckPosicionesValidas(fil, col);
	int i = 0;
	while (get<0>(datos[fil][i]) != col){
		i++;
	}
	return get<1>(datos[fil][i]);
}

void MatrizLIL::SetTamano(const unsigned int filas, const unsigned int columnas)
{
	Matriz::SetTamano(filas, columnas);
	datos.clear();
}

MatrizStandard MatrizLIL::operator*(const Matriz& m2)
{
	assert(GetCantidadColumnas() == m2.GetCantidadFilas());

	MatrizStandard result = MatrizStandard(GetCantidadFilas(), m2.GetCantidadColumnas(), 0);

	for (unsigned int i = 0; i < GetCantidadFilas(); i++){
		if (datos[i].size() > 0){ //recorro filas de MatrizLIL, si es nula la ignoro
			for (unsigned int j = 0; j < m2.GetCantidadColumnas(); j++){ // recorro las columnas donde voy a calcular el valor
				float accum = 0;
				for (unsigned int k = 0; k < datos[i].size(); k++){
					accum += get<1>(datos[i][k]) * m2.Get(get<0>(datos[i][k]), j); //fila * columna
					result.Set(i,j, accum);
				}
			}
		}
	}

	return result;
}

MatrizStandard* MatrizLIL::CalcularGradoOptimizado()
{
	MatrizStandard* result = new MatrizStandard(GetCantidadFilas(), GetCantidadColumnas(), 0);

	for (unsigned int i = 0; i < GetCantidadColumnas(); i++)
	{
		unsigned int tamCol = 0;
		for (unsigned int j = 0; i < GetCantidadFilas(); i++){ //recorro MatrizLIL buscando valores en la columna i;
			for (unsigned int k = 0; j < datos[j].size(); k++){
				if (get<0>(datos[j][k]) == i){
					tamCol += 1;
				}
			}
		}

		if(tamCol == 0)
		{
			result->Set(i, i, 0);
		}
		else
		{
			result->Set(i, i, (float)1 / tamCol);
		}
	}

	return result;
}

MatrizLIL::~MatrizLIL(){
// hay que poner algo aca?
}
