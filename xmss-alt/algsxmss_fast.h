// Distributed under the MIT software license, see the accompanying
// file LICENSE or http://www.opensource.org/licenses/mit-license.php.
// Based on the public domain XMSS reference implementation
// by Andreas Hülsing and Joost Rijneveld
/*
xmss_fast.h version 20160722
Andreas Hülsing
Joost Rijneveld
Public domain.
*/

#ifndef XMSSALT_XMSS_FAST_H
#define XMSSALT_XMSS_FAST_H

#include <cstddef>
#include "wots.h"

typedef struct{
  wots_params wots_par;
  unsigned int n;
  unsigned int h;
  unsigned int k;
} xmssfast_params;

typedef struct{
  unsigned int h;
  unsigned int next_idx;
  unsigned int stackusage;
  unsigned char completed;
  unsigned char *node;
} treehash_inst;

typedef struct {
  unsigned char *stack;
  unsigned int stackoffset;
  unsigned char *stacklevels;
  unsigned char *auth;
  unsigned char *keep;
  treehash_inst *treehash;
  unsigned char *retain;
  unsigned int next_leaf;
} bds_state;

/**
 * Initialize BDS state struct
 * parameter names are the same as used in the description of the BDS traversal
 */
void xmss_set_bds_state(bds_state *state, unsigned char *stack, unsigned int stackoffset, unsigned char *stacklevels, unsigned char *auth, unsigned char *keep, treehash_inst *treehash, unsigned char *retain, unsigned int next_leaf);
/**
 * Initializes parameter set.
 * Needed, for any of the other methods.
 */
int xmssfast_set_params(xmssfast_params *params, int n, int h, int w, int k);
/**
 * Initialize xmssmt_params struct
 * parameter names are the same as in the draft
 * 
 * Especially h is the total tree height, i.e. the XMSS trees have height h/d
 */
/**
 * Generates a XMSS key pair for a given parameter set.
 * Format sk: [(32bit) idx || SK_SEED || SK_PRF || PUB_SEED || root]
 * Format pk: [root || PUB_SEED] omitting algo oid.
 */
int xmssfast_Genkeypair(unsigned char *pk, unsigned char *sk, bds_state *state, unsigned char *seed, unsigned char h);
/**
 * Signs a message.
 * Returns 
 * 1. an array containing the signature followed by the message AND
 * 2. an updated secret key!
 * 
 */
int xmssfast_Signmsg(unsigned char *sk, bds_state *state, unsigned char *sig_msg,unsigned char *msg,unsigned long long msglen, unsigned char h);
/**
 * Verifies a given message signature pair under a given public key.
 * 
 * Note: msg and msglen are pure outputs which carry the message in case verification succeeds. The (input) message is assumed to be within sig_msg which has the form (sig||msg). 
 */
int xmssfast_Verifysig(unsigned char *msg,unsigned long long msglen, unsigned char *sig_msg,const unsigned char *pk, unsigned char h);
int xmssfast_update(unsigned char *sk, bds_state *state, unsigned long h, unsigned long new_idx);

#endif // XMSSALT_XMSS_FAST_H
