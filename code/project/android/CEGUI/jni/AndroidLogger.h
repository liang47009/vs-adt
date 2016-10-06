/*
 * AndroidLogger.h
 *
 *  Created on: 2016年10月5日
 *      Author: XIAYUNFENG
 */

#ifndef ANDROIDLOGGER_H_
#define ANDROIDLOGGER_H_

#include <android/log.h>

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "CEGUI", __VA_ARGS__)




#endif /* ANDROIDLOGGER_H_ */
