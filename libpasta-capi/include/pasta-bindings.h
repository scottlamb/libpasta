#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * Holds possible configuration options
 * See the [module level documentation](index.html) for more information.
 */
typedef struct Config Config;

/*
 * Password hashing primitives
 *
 * Each variant is backed up by different implementation.
 * Internally, primitives can either be static values, for example,
 * the `lazy_static` generated value `DEFAULT_PRIM`, or dynamically allocated
 * variables, which are `Arc<Box<...>>`.
 *
 * Most operations are expected to be performed using the static functions,
 * since most use the default algorithms. However, the flexibilty to support
 * arbitrary parameter sets is essential.
 */
typedef struct Primitive Primitive;

char *config_hash_password(const Config *config, const char *password);

char *config_migrate_hash(const Config *config, const char *hash);

bool config_verify_password(const Config *config, const char *hash, const char *password);

bool config_verify_password_update_hash(const Config *config,
                                        const char *hash,
                                        const char *password,
                                        char **new_hash);

Config *config_with_primitive(const Primitive *prim);

Primitive *default_argon2i();

Primitive *default_bcrypt();

Primitive *default_pbkdf2i();

Primitive *default_scrypt();

void free_Config(Config *config);

void free_Primitive(Primitive *prim);

void free_string(char *s);

char *hash_password(const char *password);

char *migrate_hash(const char *hash);

Primitive *new_argon2i(unsigned int passes, unsigned int lanes, unsigned int kib);

Primitive *new_bcrypt(unsigned int cost);

Primitive *new_scrypt(unsigned char log_n, unsigned int r, unsigned int p);

char *read_password(const char *prompt);

bool verify_password(const char *hash, const char *password);

bool verify_password_update_hash(const char *hash, const char *password, char **new_hash);