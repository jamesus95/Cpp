
#ifndef userfactory_h
#define userfactory_h

#define USER_TYPES 1

class UserFactory : public ItemFactory {
    
public:
    
    UserFactory();
    UserFactory(UserFactory&);
    ~UserFactory();
    
    Customer* createUser(char userCode) const;
    
    
private:
    
    Customer* originalUserTypes[USER_TYPES];
    int hash(char ch) const;    // maps user code to correct constructor    
};

#endif
