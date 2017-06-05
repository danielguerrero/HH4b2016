#ifndef GAUSSEXP
#define GAUSSEXP

 
class GaussExp : public RooAbsPdf {
public:
  GaussExp() {} ; 
  GaussExp(const char *name, const char *title,
	      RooAbsReal& _x,
	      RooAbsReal& _p0,
	      RooAbsReal& _p1,
	      RooAbsReal& _p2);
  GaussExp(const GaussExp& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new GaussExp(*this,newname); }
  inline virtual ~GaussExp() { }

protected:

  RooRealProxy x ;
  RooRealProxy p0 ;
  RooRealProxy p1 ;
  RooRealProxy p2 ;
  
  Double_t evaluate() const ;

private:

  ClassDef(GaussExp,1) // Your description goes here...
};
 
#endif
