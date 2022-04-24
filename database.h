#ifndef DATABASE_H
#define DATABASE_H


class Database{
    public:
        void connectDB(bool dbExists);
        void createTables();
};


#endif // DATABASE_H
