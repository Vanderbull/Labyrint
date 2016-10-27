class Particle
{
    private:
    //Offsets
    int x, y;
    
    //Current frame of animation
    int frame;
    
    //Type of particle
    //SDL_Surface *type;
    
    public:
    //Constructor
    Particle( int X, int Y );
    
    //Shows the particle
    void show();

    //Checks if particle is dead
    bool is_dead();
};

Particle::Particle( int X, int Y )
{
    //Set offsets
    x = X - 5 + ( rand() % 25 );
    y = Y - 5 + ( rand() % 25 );
    
    //Initialize animation
    frame = rand() % 5;
    
    //Set type
    switch( rand() % 3 )
    {
        case 0: SetPixel(hdc,x,y,RGB(255,0,0)); break;
        case 1: SetPixel(hdc,x,y,RGB(0,255,0)); break;
        case 2: SetPixel(hdc,x,y,RGB(0,0,255)); break;
    }
}

void Particle::show()
{
    //Show image
    //apply_surface( x, y, type, screen );
    
    //Show shimmer
    if( frame % 2 == 0 )
    {
		SetPixel(hdc,x,y,RGB(255,255,255));
        //apply_surface( x, y, shimmer, screen );    
    }
    
    //Animate
    frame++;
}

bool Particle::is_dead()
{
    if( frame > 10 )
    {
        return true;    
    }
    
    return false;
}

