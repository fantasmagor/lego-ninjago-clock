#ifndef Included_Element

#define Included_Element
class Element {
  private:
    char* _name;
  public:
    Element ();
    virtual void next();
    char* getName();
    void setName(char*);
};

Element::Element () {}
void Element::next() {
//  Serial.println("Element");
};

char* Element::getName() {
  return _name;
};

void Element::setName(char* name) {
  _name = name;
};

#endif
