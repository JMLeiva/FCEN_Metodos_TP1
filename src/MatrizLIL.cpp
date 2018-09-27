/*
 * MatrizLIL.cpp
 *
 *  Created on: Sep 25, 2018
 *      Author: jorgedavid
 */

#include "MatrizLIL.h"
#include "helpers/Tools.h"
#include <assert.h>

MatrizLIL::MatrizLIL(const MatrizLIL &m) : Matriz(m.GetCantidadFilas(), m.GetCantidadColumnas())
{
    datos.clear();

    datos.resize(m.datos.size());
    for (unsigned f = 0; f < m.GetCantidadFilas(); f++)
    {
        datos[f] = m.datos[f];

    }
}

MatrizLIL::MatrizLIL(const unsigned int &filas, const unsigned int &columnas) : Matriz(filas, columnas)
{
    datos = (std::vector<std::vector<std::tuple<int, float>>>)(filas);
    for (unsigned f = 0; f < filas; f++){
        std::vector<std::tuple<int, float>> nv_f;
        datos.push_back(nv_f);
    }
}

MatrizLIL::MatrizLIL(const unsigned int &filas, const unsigned int &columnas, const float &elem) : Matriz(filas, columnas)
{
    datos = (std::vector<std::vector<std::tuple<int, float>>>)(filas);
    for (unsigned f = 0; f < filas; f++)
    {
        if (Tools::EsNulo(elem))
            return;
        datos[f] = std::vector<std::tuple<int, float>>(columnas);
        for (unsigned c = 0; c < filas; c++)
        {
            datos[f].push_back(std::tuple<int, float>(c, elem));
        }
    }
}

Matriz* MatrizLIL::CrearIdentidad(const unsigned int &tam)
{
    Matriz* id = new MatrizLIL(tam,tam, 0);

    for(unsigned int i = 0; i < tam; i++)
    {
        id->Set(i, i, 1);
    }

    return id;
}

void MatrizLIL::Set(const unsigned int fila, const unsigned int columna, const float elem)
{
    Matriz::CheckPosicionesValidas(fila, columna);

    if (Tools::EsNulo(elem)) {
        return;
    }

    for (unsigned c = 0; c < datos[fila].size(); c++){            //Se fija si el valor esta. Si lo esta, lo borra
        bool esta = std::get<0>(datos[fila][c]) == columna;
        if (esta)
            datos[fila].erase(datos[fila].begin()+c);
    }
    datos[fila].push_back(std::tuple<int, float>(columna, elem));           //Agrega el valor en la fila
    for (int c = datos[fila].size() - 1; c > 0; c--){                       //correspondiente y ordena la fila
        if (std::get<1>(datos[fila][c]) < std::get<1>(datos[fila][c-1]))
            swap(datos[fila][c], datos[fila][c-1]);
        else
            break;
    }

}

float MatrizLIL::Get(const unsigned int fila, const unsigned int columna) const
{
    CheckPosicionesValidas(fila,columna);
    for (const auto &c : datos[fila]) {
        if (std::get<0>(c) == columna)
            return std::get<1>(c);
    }

    return 0;
}

Matriz* MatrizLIL::Copiar() const
{
    Matriz* nv_m = new MatrizLIL(*this);
    return nv_m;
}

void MatrizLIL::Sumar(const Matriz &m)
{
    assert(GetCantidadFilas() == m.GetCantidadFilas());
    assert(GetCantidadColumnas() == m.GetCantidadColumnas());

    for (unsigned f = 0; f < GetCantidadFilas(); f++){
        for (unsigned c = 0; c < GetCantidadColumnas(); c++)
            Set(f,c, Get(f,c) + m.Get(f,c));
    }
}

void MatrizLIL::Restar(const Matriz &m)
{
    assert(GetCantidadFilas() == m.GetCantidadFilas());
    assert(GetCantidadColumnas() == m.GetCantidadColumnas());

    for (unsigned f = 0; f < GetCantidadFilas(); f++){
        for (unsigned c = 0; c < GetCantidadColumnas(); c++)
            Set(f,c, Get(f,c) - m.Get(f,c));
    }
}

void MatrizLIL::Multiplicar(const float &elem)
{
    for (unsigned f = 0; f < GetCantidadFilas(); f++){
        for (unsigned c = 0; c < GetCantidadColumnas(); c++)
            Set(f,c, elem * Get(f,c));
    }
}

void MatrizLIL::Multiplicar(const Matriz &m)
{
    assert(GetCantidadColumnas() == m.GetCantidadFilas());

    for (unsigned f = 0; f < GetCantidadFilas(); f++){
        if (datos[f].size() > 0){
            for (unsigned m_c = 0; m_c < m.GetCantidadColumnas(); m_c++){
                float acum = 0;
                for (auto &c : datos[f]) {
                    acum += std::get<1>(c) * m.Get(std::get<0>(c), m_c);
                }
                if(!Tools::EsNulo(acum))
                    Set(f,m_c,acum);

            }
        }
    }
}

void MatrizLIL::Escalonar()
{
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

void MatrizLIL::Extender(const Vector &v)
{
    assert(v.GetTamano() == GetCantidadFilas());
    SetTamano(GetCantidadFilas(), GetCantidadColumnas()+1);

    for(unsigned int fil = 0; fil < GetCantidadFilas(); fil++)
    {
        Set(fil, GetCantidadColumnas()-1, v.Get(fil));
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



MatrizLIL::~MatrizLIL()
{

}
