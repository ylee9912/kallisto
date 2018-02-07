#ifndef KALLISTO_PLAINTEXT_WRITER_H
#define KALLISTO_PLAINTEXT_WRITER_H

#include <assert.h>
#include <cstdlib>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "KmerIndex.h"

void plaintext_writer(
    const std::string& out_name,
    const std::vector<std::string>& targ_ids,
    const std::vector<double>& alpha,
    const std::vector<double>& eff_lens,
    const std::vector<int>& lens
    );

std::string to_json(const std::string& id, const std::string& val, bool quote,
    bool comma = true, int level = 1);

void plaintext_aux(
    const std::string& out_fname,
    const std::string& n_targs,
    const std::string& n_bootstrap,
    const std::string& n_processed,
    const std::string& n_pseudoaligned,
    const std::string& n_unique,
    const std::string& version,
    const std::string& index_v,
    const std::string& start_time,
    const std::string& call);

void writeBatchMatrix(
  const std::string &prefix,
  const KmerIndex &index,
  const std::vector<std::string> &ids,
  std::vector<std::vector<int>> &counts);

void writeCellIds(
  const std::string &filename,
  const std::vector<std::string> &ids);


void writeECList(
  const std::string &filename,
  const KmerIndex &index);

void writeFLD(const std::string &filename, const std::vector<std::pair<double, double>> &flds);


template<typename T>
void writeSparseBatchMatrix(
  const std::string &filename,
  std::vector<std::vector<std::pair<int,T>>> &data, int cols) {

  std::ofstream of;
  int num_rows = data.size();
  int num_cols = cols;
  int num_entries = 0;
  for (size_t j = 0; j < data.size(); j++) {
    const auto &v = data[j];
    for (size_t i = 0; i < v.size(); i++) {
      if (v[i].second != T(0)) {
        num_entries++;
      }
    }
  }
  of.open(filename.c_str(), std::ios::out);
  of << num_rows << "\t" << num_cols << "\t" << num_entries << "\n";
  if (!data.empty()) {      
    for (size_t j = 0; j < data.size(); j++) {
      const auto &v = data[j];
      for (size_t i = 0; i < v.size(); i++) {
        if (v[i].second != T(0)) {
          of << j << "\t" << v[i].first << "\t" << v[i].second << "\n";
        }
      }
    }
  }
  of.close();
}


#endif
