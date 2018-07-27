
/* STRUCTURE timerInput
 * Data type template for timer to read and modify.
 *
 * Input: double masterPrescaler,double masterPeriod,double masterReps,double slavePrescaler;double slavePeriod,double slavePulse,double slaveReps;
 * Output: void
*/

struct timerInput {
  double masterPrescaler;
  double masterPeriod;
  double masterReps;

  double slavePrescaler;
  double slavePeriod;
  double slavePulse;
  double slaveReps;
};