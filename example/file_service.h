/**
 * @file file_service.h
 * @brief
 * @author boo
 * @copyright
 */

#ifndef FILE_SERVICE_H
#define FILE_SERVICE_H

#include "ios.h"

class FileService : public FACE::IOSS::IOService {
 public:
  FileService(const std::string &name);
  virtual ~FileService();

  virtual int32_t open();
  virtual int32_t close();
  virtual int32_t read(uint8_t *buf, const uint32_t size);
  virtual int32_t write(const uint8_t *buf, const uint32_t size);
  virtual int32_t ioctl(void *target, const int32_t op);
};

#endif
