#pragma once

#include "stdbool.h"
#include "stdio.h"

#include "villages.h"

#define EKOPARTY_V_STR "EkoParty"
#define HW_HACK_V_STR "Hardware Hacking"
#define BIT_CANA_V_STR "A 1 bit de ir en cana"
#define BLUE_SPACE_V_STR "Blu Space"
#define RED_TEAM_V_STR "Red Team"
#define CYB_FIN_V_STR "Cyber Finance"
#define HAMPING_V_STR "Hamping"
#define BUG_BOU_SPA_V_STR "Bug Bounty Space"
#define SOCIAL_ENG_V_STR "Social Engineering"
#define PAT_SPACE_V_STR "Patagon Space"
#define BLOCK_SEC_V_STR "Blockchain Security"
#define DEV_SEC_OPS_V_STR "DevSecOps"
#define SASO_CONF_V_STR "SASOConf"
#define CAR_HACK_V_STR "Car Hacking"
#define MOB_HACK_V_STR "Mobile Hacking"
#define EC_V_STR "Electronic Cats"
#define CHICHES_ASADO_V_STR "Asado de Chiche"
#define THE_BOSS_1_V_STR "EKO Boss1"
#define THE_BOSS_2_V_STR "EKO Boss2"

#define EKOPARTY_H_STR "E*o*a*t*"
#define HW_HACK_H_STR "H*r*w*r* H*c*i*g"
#define BIT_CANA_H_STR "A * b*t *e *r *n *a*a"
#define BLUE_SPACE_H_STR "B*u *p*c*"
#define RED_TEAM_H_STR "R*d *e*m"
#define CYB_FIN_H_STR "C*b*r *i*a*c*"
#define HAMPING_H_STR "H*m*i*g"
#define BUG_BOU_SPA_H_STR "B*g *o*n*y *p*c*"
#define SOCIAL_ENG_H_STR "S*c*a* E*g*n*e*i*g"
#define PAT_SPACE_H_STR "P*t*g*n *p*c*"
#define BLOCK_SEC_H_STR "*l*c*c*a*n *e*u*i*y"
#define DEV_SEC_OPS_H_STR "D*v*e*O*s"
#define SASO_CONF_H_STR "S*S*C*n*"
#define CAR_HACK_H_STR "C*r *a*k*n*"
#define MOB_HACK_H_STR "*b*l* H*c*i*g"
#define EC_H_STR "E*e*t*o*i* C*t*"
#define CHICHES_ASADO_H_STR "*s*d* d* C*i*h*"
#define THE_BOSS_1_H_STR "*K* B*s*1"
#define THE_BOSS_2_H_STR "*K* B*s*2"

typedef struct {
  const char *name;
  const char *name_hint;
  char **details;
  uint8_t details_len;
  bool found;
} almanac_village_t;

const char *ekoparty_details[] = {EKOPARTY_V_STR, "Lorem Ipsum"};
const char *hw_hack_details[] = {HW_HACK_V_STR, "Lorem Ipsum"};
const char *bit_cana_details[] = {BIT_CANA_V_STR, "Lorem Ipsum"};
const char *blue_space_details[] = {BLUE_SPACE_V_STR, "Lorem Ipsum"};
const char *red_team_details[] = {RED_TEAM_V_STR, "Lorem Ipsum"};
const char *cyb_fin_details[] = {CYB_FIN_V_STR, "Lorem Ipsum"};
const char *hamping_details[] = {HAMPING_V_STR, "Lorem Ipsum"};
const char *bug_bou_spa_details[] = {BUG_BOU_SPA_V_STR, "Lorem Ipsum"};
const char *social_eng_details[] = {SOCIAL_ENG_V_STR, "Lorem Ipsum"};
const char *pat_space_details[] = {PAT_SPACE_V_STR, "Lorem Ipsum"};
const char *block_sec_details[] = {BLOCK_SEC_V_STR, "Lorem Ipsum"};
const char *dev_sec_ops_details[] = {DEV_SEC_OPS_V_STR, "Lorem Ipsum"};
const char *saso_conf_details[] = {SASO_CONF_V_STR, "Lorem Ipsum"};
const char *car_hack_details[] = {CAR_HACK_V_STR, "Lorem Ipsum"};
const char *mob_hack_details[] = {MOB_HACK_V_STR, "Lorem Ipsum"};
const char *ec_details[] = {EC_V_STR, "Lorem Ipsum"};
const char *chiches_asado_details[] = {CHICHES_ASADO_V_STR, "Lorem Ipsum"};
const char *the_boss_1_details[] = {THE_BOSS_1_V_STR, "Lorem Ipsum"};
const char *the_boss_2_details[] = {THE_BOSS_2_V_STR, "Lorem Ipsum"};

const char *village_not_found[] = {"  !!!VACIO!!! ", "Explora todas",
                                   "las villas para", "completar el",
                                   "almanaque"};

almanac_village_t almanac[] = {{.name = EKOPARTY_V_STR,
                                .name_hint = EKOPARTY_H_STR,
                                .details = ekoparty_details,
                                .details_len = 2,
                                .found = false},
                               {.name = HW_HACK_V_STR,
                                .name_hint = HW_HACK_H_STR,
                                .details = hw_hack_details,
                                .details_len = 2,
                                .found = false},
                               {.name = BIT_CANA_V_STR,
                                .name_hint = BIT_CANA_H_STR,
                                .details = bit_cana_details,
                                .details_len = 2,
                                .found = false},
                               {.name = BLUE_SPACE_V_STR,
                                .name_hint = BLUE_SPACE_H_STR,
                                .details = blue_space_details,
                                .details_len = 2,
                                .found = false},
                               {.name = RED_TEAM_V_STR,
                                .name_hint = RED_TEAM_H_STR,
                                .details = red_team_details,
                                .details_len = 2,
                                .found = false},
                               {.name = CYB_FIN_V_STR,
                                .name_hint = CYB_FIN_H_STR,
                                .details = cyb_fin_details,
                                .details_len = 2,
                                .found = false},
                               {.name = HAMPING_V_STR,
                                .name_hint = HAMPING_H_STR,
                                .details = hamping_details,
                                .details_len = 2,
                                .found = false},
                               {.name = BUG_BOU_SPA_V_STR,
                                .name_hint = BUG_BOU_SPA_H_STR,
                                .details = bug_bou_spa_details,
                                .details_len = 2,
                                .found = false},
                               {.name = SOCIAL_ENG_V_STR,
                                .name_hint = SOCIAL_ENG_H_STR,
                                .details = social_eng_details,
                                .details_len = 2,
                                .found = false},
                               {.name = PAT_SPACE_V_STR,
                                .name_hint = PAT_SPACE_H_STR,
                                .details = pat_space_details,
                                .details_len = 2,
                                .found = false},
                               {.name = BLOCK_SEC_V_STR,
                                .name_hint = BLOCK_SEC_H_STR,
                                .details = block_sec_details,
                                .details_len = 2,
                                .found = false},
                               {.name = DEV_SEC_OPS_V_STR,
                                .name_hint = DEV_SEC_OPS_H_STR,
                                .details = dev_sec_ops_details,
                                .details_len = 2,
                                .found = false},
                               {.name = SASO_CONF_V_STR,
                                .name_hint = SASO_CONF_H_STR,
                                .details = saso_conf_details,
                                .details_len = 2,
                                .found = false},
                               {.name = CAR_HACK_V_STR,
                                .name_hint = CAR_HACK_H_STR,
                                .details = car_hack_details,
                                .details_len = 2,
                                .found = false},
                               {.name = MOB_HACK_V_STR,
                                .name_hint = MOB_HACK_H_STR,
                                .details = mob_hack_details,
                                .details_len = 2,
                                .found = false},
                               {.name = EC_V_STR,
                                .name_hint = EC_H_STR,
                                .details = ec_details,
                                .details_len = 2,
                                .found = false},
                               {.name = CHICHES_ASADO_V_STR,
                                .name_hint = CHICHES_ASADO_H_STR,
                                .details = chiches_asado_details,
                                .details_len = 2,
                                .found = false},
                               {.name = THE_BOSS_1_V_STR,
                                .name_hint = THE_BOSS_1_H_STR,
                                .details = the_boss_1_details,
                                .details_len = 2,
                                .found = false},
                               {.name = THE_BOSS_2_V_STR,
                                .name_hint = THE_BOSS_2_H_STR,
                                .details = the_boss_2_details,
                                .details_len = 2,
                                .found = false}};

void almanac_load_items();
void almanac_unlock_item(villages_e village);