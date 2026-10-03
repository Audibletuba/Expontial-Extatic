//System 

//Engine
#include "Object.h"
#include "EventCollision.h"

namespace df
{
    class Enemy : public Object
    {
        private:
            int eventHandler(const Event *p_e) override;
            void out();
            void moveToStart();
        public:
            Enemy();
            ~Enemy();
            void hit(const EventCollision *p_c);
    };

}//End of namespace df