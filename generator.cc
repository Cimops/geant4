#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
    fParticleGun = new G4ParticleGun(1); // one run, but several events
                                        // one event?

}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
    delete fParticleGun;

}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable(); // define this particle, and we wanna to find it
                                                                    // in our list

    G4String particleName = "proton";
    G4ParticleDefinition *particle = particleTable->FindParticle("proton");

    G4ThreeVector pos(0., 0., 0.); // centre of mother volume
    G4ThreeVector mom(0., 0., 1.); // z-direction

    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(mom);
    fParticleGun->SetParticleMomentum(100.*GeV);
    fParticleGun->SetParticleDefinition(particle);

    fParticleGun->GeneratePrimaryVertex(anEvent);
    
}
