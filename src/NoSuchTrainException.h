#ifndef NOSUCHTRAINEXCEPTION_H_
#define NOSUCHTRAINEXCEPTION_H_

#include "TrainSystemException.h"
#include "project_types.h"


class NoSuchTrainException: public TrainSystemException {
public:
	NoSuchTrainException(id_t id);
	std::string what();
private:
	id_t id;
};

#endif /* NOSUCHTRAINEXCEPTION_H_ */