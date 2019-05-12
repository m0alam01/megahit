//
// Created by vout on 4/28/19.
//

#ifndef MEGAHIT_FASTX_READER_H
#define MEGAHIT_FASTX_READER_H

#include <vector>
#include <string>
#include "kseq.h"
#include <zlib.h>
#include "base_reader.h"
#include "definitions.h"

#ifndef KSEQ_INITED
#define KSEQ_INITED
KSEQ_INIT(gzFile, gzread)
#endif

class FastxReader : public BaseSequenceReader {
 public:
  explicit FastxReader(const std::string &file_name);
  virtual ~FastxReader();
  virtual int64_t Read(SeqPackage *pkg, int64_t max_num, int64_t max_num_bases, bool reverse, bool trim_n);
  static void TrimN(const char *s, int len, int *out_bpos, int *out_epos);

  kseq_t *ReadNext() {
    if (kseq_reader_ && kseq_read(kseq_reader_) >= 0) {
      return kseq_reader_;
    } else {
      return nullptr;
    }
  }

  gzFile fp_{};
  kseq_t *kseq_reader_{};
};

#endif //MEGAHIT_FASTX_READER_H
