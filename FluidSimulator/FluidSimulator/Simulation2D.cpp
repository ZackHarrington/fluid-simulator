#include "Simulation2D.h"

/* Public Member Functions */
void Simulation2D::update(const float deltaTime)
{
    //float totalEnergy = 0;
    for (int i = 0; i < particles.getSize(); i++)
    {
        float t = 0;
        FVector newPosition = particles[i].nextUpdatePosition(deltaTime);

        //totalEnergy +=  0.5f * particles[i].getMass() * pow(particles[i].getVelocity().getLength(), 2);

        // Check particle collisions
        for (int j = i + 1; j < particles.getSize(); j++)
        {
            if (newPosition.getDistance(particles[j].getPosition()) <
                particles[i].getRadius() + particles[j].getRadius())
            {
                collide(particles[i], particles[j]);
            }
        }
        // ***** Will implement after finishing OpenGL tutorial and better understanding collision detection *****
        /*for (int j = i + 1; j < particles.getSize(); j++)
        {
            t = getCollisionTime(particles[i], particles[j]);
            if (t != NULL && t > 0 && t < deltaTime)
            {
                collide(particles[i], particles[j]);
            }
        }*/

        // Check edge collisions
        for (int j = 0; j < lines.getSize(); j++)
        {
            t = getCollisionTime(particles[i], lines[j]);
            if (t != NULL && t > 0 && t < deltaTime)
            {
                collide(particles[i], lines[j]);
            }
        }

        // Update the particle
        particles[i].update(deltaTime);
    }

    /*energyCount++;
    energySinceStart += totalEnergy;
    std::cout << initialEnergy << "\t" << energySinceStart/energyCount << std::endl;*/
}


/* Private Member Functions */
float Simulation2D::getCollisionTime(const Particle2D& p1, const Particle2D& p2)
{
    // For math see: notes > math > time_until_distance (page 1 - 2)
    float deltaPx = p2.getPosition()[0] - p1.getPosition()[0];
    float deltaPy = p2.getPosition()[1] - p1.getPosition()[1];
    float deltaVx = p2.getVelocity()[0] - p1.getVelocity()[0];
    float deltaVy = p2.getVelocity()[1] - p1.getVelocity()[1];
    FVector deltaP = p2.getPosition() - p1.getPosition();
    FVector deltaV = p2.getVelocity() - p1.getVelocity();

    return quadraticFormula(
        pow(deltaVx, 2) + pow(deltaVy, 2), 
        2 * (deltaV * deltaP), 
        pow(deltaPx, 2) + pow(deltaPy, 2) - pow(p1.getRadius() + p2.getRadius(), 2), 
        false);
}
float Simulation2D::getCollisionTime(const Particle2D& p, const Line& l)
{
    // For math see: notes > math > time_until_distance (page 1)
    FVector c(2U, new float[] {
        l.getPosition2()[1] - l.getPosition1()[1], 
            l.getPosition1()[0] - l.getPosition2()[0]});
    return (-p.getRadius() * l.getLength() - p.getPosition() * c -
        l.getPosition1()[1] * l.getPosition2()[0] + l.getPosition1()[0] * l.getPosition2()[1]) /
        (p.getVelocity() * c);
}

void Simulation2D::collide(Particle2D& p1, Particle2D& p2)
{
    // From wikipedia
    // v1' = v1 - 2*m2/(m1+m2) * ((v1 - v2) dot (x1 - x2)) / (||x1 - x2||^2) * (x1 - x2)
    // v2' = v2 - 2*m1/(m1+m2) * ((v2 - v1) dot (x2 - x1)) / (||x2 - x1||^2) * (x2 - x1)
    // need to swap around the last * (x1 - x2) to fit my overloaded operators
    /*FVector v1prime = velocity - (position - p.getPosition()) * (((2 * p.getMass()) / (mass + p.getMass())) *
        ((velocity - p.getVelocity()) * (position - p.getPosition())) / pow((position - p.getPosition()).getLength(), 2));
    FVector v2prime = p.getVelocity() - (p.getPosition() - position) * (((2 * mass) / (mass + p.getMass())) *
        ((p.getVelocity() - velocity) * (p.getPosition() - position)) / pow((p.getPosition() - position).getLength(), 2));

    setVelocity(v1prime);
    p.setVelocity(v2prime);*/

    // My Math
    // collision normal unit vector		n1to2 = (P2 - P1) / |P2 - P1|
    // collision tangential unit vector u = (-n1to2.Y, n1to2.X)			- counter clockwise fron n1to2, though it doesn't much matter
    // normal velocity component		Vn = proj(n1to2, V)				- where proj(n, V) = ((V * n) / |n|^2) * n
    // tangential velocity component	Vt = proj(u, V)					- ^
    // force is appied in the direction normal to the collision so we apply the 1D motion equations to the normal velocity components
    //  and leave the tangential components alone
    // w/out friction or resilience		V1 = V1t + (m1-m2)/(m1+m2) * V1n + (2*m2)/(m1+m2) * V2n
    //                                  V2 = V2t + (2*m1)/(m1+m2) * V1n + (m2-m1)/(m1+m2) * V2n
    FVector n1to2 = p2.getPosition() - p1.getPosition();
    n1to2.normalize();
    FVector tangentialDir = FVector(2U, new float[] {-n1to2[1], n1to2[0]});
    FVector V1normal = n1to2 * (p1.getVelocity() * n1to2);						// Adjusted to fit my overloaded operators
    FVector V1tangential = tangentialDir * (p1.getVelocity() * tangentialDir);	// ^ and the other vectors are unit vectors so 
    FVector V2normal = n1to2 * (p2.getVelocity() * n1to2);						// ^ I dropped the 1^2 from the denominator
    FVector V2tangential = tangentialDir * (p2.getVelocity() * tangentialDir);	// ^
    float m1 = p1.getMass();
    float m2 = p2.getMass();
    p1.setVelocity(V1tangential + (V1normal*(m1-m2) + V2normal*(2*m2)) / (m1+m2));
    p2.setVelocity(V2tangential + (V1normal*(2*m1) + V2normal*(m2-m1)) / (m1+m2));
}
void Simulation2D::collide(Particle2D& p, Line& l)
{
    // Roughly the same math as a particle on particle collision but we flip Vn instead of transferring it
    FVector n = FVector(2U, new float[] {-l.getDirection()[1], l.getDirection()[0]});
    FVector Vn = n * (p.getVelocity() * n);										// Same as particle on particle
    FVector Vt = l.getDirection() * (p.getVelocity() * l.getDirection());		// ^
    p.setVelocity(Vt - Vn);
}

float Simulation2D::quadraticFormula(float a, float b, float c, bool returnPlus)
{
    float underSquareroot = pow(b, 2) - 4 * a * c;
    if (underSquareroot < 0)
        return NULL;
    if (a == 0)
        return NULL;

    if (returnPlus)
        return (-b + sqrt(underSquareroot)) / (2 * a);
    else
        return (-b - sqrt(underSquareroot)) / (2 * a);
}