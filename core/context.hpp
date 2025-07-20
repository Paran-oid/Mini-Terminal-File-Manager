#ifndef CONTEXT_H
#define CONTEXT_H

struct Cursor {
    int32_t cx, cy, rx;
};

class Context {
   private:
    Cursor m_cursor;
    std::vector<std::string> m_commands;

    std::string working_dir;

   public:
    Context(void) = 0;
    ~Context() = 0;

    Cursor cursor_get(void);
    void cursor_set(Cursor cursor);

    Cursor working_dir_get(void);
    void working_dir_set(std::string cursor);
};



#endif