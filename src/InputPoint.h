#ifndef INPUTPOINT_H
#define INPUTPOINT_H

#include "InputFile.h"
#include "InputParams.h"
#include <string>
#include <vector>


class InputPoint
{
public:
    InputPoint(int index, const InputFile& file, const InputParams& params, int& tFloor, int& tCeil, double& moy_errij2);
    virtual ~InputPoint();

private:
    double parseDouble(const std::string& str);

public:

    std::string m_ident;
    int m_index_crav;

    double m_tdij1;
    double m_tdij2;
    double m_tdijm;
    double m_tdij;

    double m_tij; // temps du "Fait"
    double m_Ect_tij;
    double m_Vtij;    // variance bayésienne sur le Fait tij

    double m_nuij; // Pas dans Rec_Pts ?

    std::vector<int> m_tij_avant;
    std::vector<int> m_tij_pendant;
    std::vector<int> m_tij_apres;

    bool m_tij_initialise;
    bool m_tij_maj_bay;

    std::string m_methode_datation;
    double m_param1;
    double m_param2;
    
    std::vector<long double> m_densite_priori_tdij;

    double m_Pij;

    std::string m_contrainte_strati;

    double m_Iij;
    double m_Dij;
    double m_Kij;
    double m_rij;
    double m_Fij;
    double m_EctFij;
    double m_rFij;

    // variables pour calcul spline en fonction de type_Var_CMT
    double m_Yij;
    double m_EctYij;
    double m_rYij;
    double m_Wij;
    double m_VGij;   // variance locale

    // coordonnées des points ij sur courbe paramétrique
    double m_XijP;
    double m_YijP;
    double m_ZijP;
};

#endif
