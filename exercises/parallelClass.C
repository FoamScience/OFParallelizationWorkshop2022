#include "parallelClass.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

scalar Foam::parallelClass::run() const
{
    // This function must send v0 from proc 0 to proc 1
    // and v1 from proc 1 to proc 0;

    // And return v1 on proc 0, and v0 on proc 1
    scalar res = -1;
    scalar v0, v1 = -1;

    if (Pstream::parRun()) {
        if (Pstream::master()) {
            v0 = 200;
            {
                // Send to slave
                OPstream toSlave(Pstream::commsTypes::blocking, Pstream::firstSlave());
                toSlave << v0;
            }

            {
                // Receive from slave
                IPstream fromSlave(Pstream::commsTypes::blocking, Pstream::firstSlave());
                res = readScalar(fromSlave);
            }
        } else {
            if (Pstream::myProcNo() == Pstream::firstSlave())
            {
                {
                    // Receive from master
                    IPstream fromMaster(Pstream::commsTypes::blocking, Pstream::masterNo());
                    res = readScalar(fromMaster);
                }

                {
                    // Send to master
                    v1 = 100;
                    OPstream toMaster(Pstream::commsTypes::blocking, Pstream::masterNo());
                    toMaster << v1;
                }
            }
        }
    } else {
        res = 100;
    }

    return res;
}

}
// ************************************************************************* //
