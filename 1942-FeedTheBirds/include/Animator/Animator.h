#ifndef AN_H
#define AN_H


class Animator
{
public:
	Animator();
	~Animator(); 
		
	//using OnProgress = std::function<void(Animator*)>;

private:
	//OnProgress onProgress;
	void* progressClosure;

protected:
	void notifyProgressed(void) {
	//	if (onProgress)(*onProgress)(this, progressClosure);
	}

public:
	template <typename Tfunc>
	void setOnProgress(const Tfunc& f) {
		onProgress = f;
	}



};

#endif