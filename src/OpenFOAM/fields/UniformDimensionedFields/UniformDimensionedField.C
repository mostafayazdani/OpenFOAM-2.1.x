/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011 OpenFOAM Foundation
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

#include "UniformDimensionedField.H"

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
Foam::UniformDimensionedField<Type>::UniformDimensionedField
(
    const IOobject& io,
    const dimensioned<Type>& dt
)
:
    regIOobject(io),
    dimensioned<Type>(dt)
{}


template<class Type>
Foam::UniformDimensionedField<Type>::UniformDimensionedField
(
    const UniformDimensionedField<Type>& rdt
)
:
    regIOobject(rdt),
    dimensioned<Type>(rdt)
{}


template<class Type>
Foam::UniformDimensionedField<Type>::UniformDimensionedField
(
    const IOobject& io
)
:
    regIOobject(io),
    dimensioned<Type>(regIOobject::name(), dimless, pTraits<Type>::zero)
{
    dictionary dict(readStream(typeName));
    this->dimensions().reset(dict.lookup("dimensions"));
    dict.lookup("value") >> this->value();
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class Type>
Foam::UniformDimensionedField<Type>::~UniformDimensionedField()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
bool Foam::UniformDimensionedField<Type>::writeData(Ostream& os) const
{
    os.writeKeyword("dimensions") << this->dimensions() << token::END_STATEMENT
        << nl;
    os.writeKeyword("value") << this->value() << token::END_STATEMENT
        << nl << nl;

    return (os.good());
}


// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

template<class Type>
void Foam::UniformDimensionedField<Type>::operator=
(
    const UniformDimensionedField<Type>& rhs
)
{
    dimensioned<Type>::operator=(rhs);
}


template<class Type>
void Foam::UniformDimensionedField<Type>::operator=
(
    const dimensioned<Type>& rhs
)
{
    dimensioned<Type>::operator=(rhs);
}


// ************************************************************************* //
