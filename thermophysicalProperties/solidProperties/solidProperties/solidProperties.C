/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2017 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "solidProperties.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    defineTypeNameAndDebug(solidProperties, 0);
    defineRunTimeSelectionTable(solidProperties,);
    defineRunTimeSelectionTable(solidProperties, dictionary);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::solidProperties::solidProperties
(
    scalar rho,
    scalar Cp,
    scalar kappa,
    scalar Hf,
    scalar emissivity
)
:
    rho_(rho),
    Cp_(Cp),
    kappa_(kappa),
    Hf_(Hf),
    emissivity_(emissivity)
{}


Foam::solidProperties::solidProperties(const dictionary& dict)
:
    rho_(dict.get<scalar>("rho")),
    Cp_(dict.get<scalar>("Cp")),
    kappa_(dict.getCompat<scalar>("kappa", {{"K", 1612}})),
    Hf_(dict.get<scalar>("Hf")),
    emissivity_(dict.get<scalar>("emissivity"))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Foam::solidProperties::readIfPresent(const dictionary& dict)
{
    dict.readIfPresent("rho", rho_);
    dict.readIfPresent("Cp", Cp_);
    dict.readIfPresentCompat("kappa", {{"K", 1612}}, kappa_);
    dict.readIfPresent("Hf_", Hf_);
    dict.readIfPresent("emissivity", emissivity_);
}


void Foam::solidProperties::writeData(Ostream& os) const
{
    os  << rho_ << token::SPACE
        << Cp_ << token::SPACE
        << kappa_ << token::SPACE
        << Hf_ << token::SPACE
        << emissivity_;
}


// * * * * * * * * * * * * * * IOStream operators  * * * * * * * * * * * * * //

Foam::Ostream& Foam::operator<<(Ostream& os, const solidProperties& s)
{
    s.writeData(os);
    return os;
}


// ************************************************************************* //
