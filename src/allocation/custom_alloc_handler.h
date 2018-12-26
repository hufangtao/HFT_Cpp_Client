#ifndef CUSTOM_ALLOC_HANDLER_H
#define CUSTOM_ALLOC_HANDLER_H

template <typename Handler>

class custom_alloc_handler
{
private:
    /* data */
public:
    using allocator_type = handler_allocator<Handler>;


    custom_alloc_handler(/* args */);
    ~custom_alloc_handler();
};

custom_alloc_handler::custom_alloc_handler(/* args */)
{
}

custom_alloc_handler::~custom_alloc_handler()
{
}


#endif