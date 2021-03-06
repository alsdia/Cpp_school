/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2016 OpenFOAM Foundation
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

#include "thermophysicalFunction.H"
#include "HashTable.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
    defineTypeNameAndDebug(thermophysicalFunction, 0);
    defineRunTimeSelectionTable(thermophysicalFunction, Istream);
    defineRunTimeSelectionTable(thermophysicalFunction, dictionary);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::autoPtr<Foam::thermophysicalFunction> Foam::thermophysicalFunction::New
(
    Istream& is
)
{
    if (debug)
    {
        InfoInFunction
            << "Constructing thermophysicalFunction"
            << endl;
    }

    const word functionType(is);

    auto cstrIter = IstreamConstructorTablePtr_->cfind(functionType);

    if (!cstrIter.found())
    {
        FatalErrorInFunction
            << "Unknown thermophysicalFunction type "
            << functionType << nl << nl
            << "Valid thermophysicalFunction types :" << endl
            << IstreamConstructorTablePtr_->sortedToc()
            << abort(FatalError);
    }

    return autoPtr<thermophysicalFunction>(cstrIter()(is));
}


Foam::autoPtr<Foam::thermophysicalFunction> Foam::thermophysicalFunction::New
(
    const dictionary& dict
)
{
    if (debug)
    {
        InfoInFunction
            << "Constructing thermophysicalFunction"
            << endl;
    }

    const word functionType(dict.get<word>("functionType"));

    auto cstrIter = dictionaryConstructorTablePtr_->cfind(functionType);

    if (!cstrIter.found())
    {
        FatalErrorInFunction
            << "Unknown thermophysicalFunction type "
            << functionType << nl << nl
            << "Valid thermophysicalFunction types are :" << endl
            << dictionaryConstructorTablePtr_->sortedToc()
            << abort(FatalError);
    }

    return autoPtr<thermophysicalFunction>(cstrIter()(dict));
}


// ************************************************************************* //
