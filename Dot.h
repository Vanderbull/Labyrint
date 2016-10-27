class Dot
{
    private:
    //The offsets
    int x, y;
    
    //The velocity of the dot
    int xVel, yVel;
    
    //The particles
    Particle *particles[ 20 ];
    
    public:
    //Initializes
    Dot();
    
    //Cleans up particles
    ~Dot();
    
    //Handles keypresses
    void handle_input();
    
    //Shows the particles
    void show_particles();
    
    //Shows the dot
    void show();
};
