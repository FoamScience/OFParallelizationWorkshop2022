#ifndef parallelClass_H
#define parallelClass_H

#include "Pstream.H"
#include "labelList.H"
#include "fvMesh.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

class parallelClass
{
public:
    // Constructors
    parallelClass(const fvMesh& mesh)
    :
        lst_(Pstream::myProcNo(), Pstream::myProcNo()),
        mesh_(mesh)
    {};
    parallelClass(parallelClass &&) = default;
    parallelClass(const parallelClass &) = default;
    // Assignment/Move operators
    parallelClass &operator=(parallelClass &&) = default;
    parallelClass &operator=(const parallelClass &) = default;
    // Destructor
    ~parallelClass() {};

    // Member methods
    labelList run() const;

protected:
    // Member variables
	labelList lst_;
    const fvMesh& mesh_;
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
