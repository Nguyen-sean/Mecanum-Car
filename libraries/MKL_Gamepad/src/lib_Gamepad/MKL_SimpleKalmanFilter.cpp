#include "Arduino.h"
#include "MKL_SimpleKalmanFilter.h"
#include <math.h>

MKL_SimpleKalmanFilter::MKL_SimpleKalmanFilter(float mea_e, float est_e, float q)
{
  _err_measure = mea_e;
  _err_estimate = est_e;
  _q = q;
}

float MKL_SimpleKalmanFilter::updateEstimate(float mea)
{
  _kalman_gain = _err_estimate / (_err_estimate + _err_measure);
  _current_estimate = _last_estimate + _kalman_gain * (mea - _last_estimate);
  _err_estimate = (1.0 - _kalman_gain) * _err_estimate + fabs(_last_estimate - _current_estimate) * _q;
  _last_estimate = _current_estimate;

  return _current_estimate;
}

void MKL_SimpleKalmanFilter::setMeasurementError(float mea_e)
{
  _err_measure = mea_e;
}

void MKL_SimpleKalmanFilter::setEstimateError(float est_e)
{
  _err_estimate = est_e;
}

void MKL_SimpleKalmanFilter::setProcessNoise(float q)
{
  _q = q;
}

float MKL_SimpleKalmanFilter::getKalmanGain()
{
  return _kalman_gain;
}
