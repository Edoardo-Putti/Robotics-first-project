;; Auto-generated. Do not edit!


(when (boundp 'lla2enu::DistanceCalculator)
  (if (not (find-package "LLA2ENU"))
    (make-package "LLA2ENU"))
  (shadow 'DistanceCalculator (find-package "LLA2ENU")))
(unless (find-package "LLA2ENU::DISTANCECALCULATOR")
  (make-package "LLA2ENU::DISTANCECALCULATOR"))
(unless (find-package "LLA2ENU::DISTANCECALCULATORREQUEST")
  (make-package "LLA2ENU::DISTANCECALCULATORREQUEST"))
(unless (find-package "LLA2ENU::DISTANCECALCULATORRESPONSE")
  (make-package "LLA2ENU::DISTANCECALCULATORRESPONSE"))

(in-package "ROS")





(defclass lla2enu::DistanceCalculatorRequest
  :super ros::object
  :slots (_x _y _x_obs _y_obs ))

(defmethod lla2enu::DistanceCalculatorRequest
  (:init
   (&key
    ((:x __x) 0.0)
    ((:y __y) 0.0)
    ((:x_obs __x_obs) 0.0)
    ((:y_obs __y_obs) 0.0)
    )
   (send-super :init)
   (setq _x (float __x))
   (setq _y (float __y))
   (setq _x_obs (float __x_obs))
   (setq _y_obs (float __y_obs))
   self)
  (:x
   (&optional __x)
   (if __x (setq _x __x)) _x)
  (:y
   (&optional __y)
   (if __y (setq _y __y)) _y)
  (:x_obs
   (&optional __x_obs)
   (if __x_obs (setq _x_obs __x_obs)) _x_obs)
  (:y_obs
   (&optional __y_obs)
   (if __y_obs (setq _y_obs __y_obs)) _y_obs)
  (:serialization-length
   ()
   (+
    ;; float64 _x
    8
    ;; float64 _y
    8
    ;; float64 _x_obs
    8
    ;; float64 _y_obs
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _x
       (sys::poke _x (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _y
       (sys::poke _y (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _x_obs
       (sys::poke _x_obs (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _y_obs
       (sys::poke _y_obs (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _x
     (setq _x (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _y
     (setq _y (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _x_obs
     (setq _x_obs (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _y_obs
     (setq _y_obs (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(defclass lla2enu::DistanceCalculatorResponse
  :super ros::object
  :slots (_distance ))

(defmethod lla2enu::DistanceCalculatorResponse
  (:init
   (&key
    ((:distance __distance) 0.0)
    )
   (send-super :init)
   (setq _distance (float __distance))
   self)
  (:distance
   (&optional __distance)
   (if __distance (setq _distance __distance)) _distance)
  (:serialization-length
   ()
   (+
    ;; float64 _distance
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _distance
       (sys::poke _distance (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _distance
     (setq _distance (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(defclass lla2enu::DistanceCalculator
  :super ros::object
  :slots ())

(setf (get lla2enu::DistanceCalculator :md5sum-) "4e22589e822a5a44dc1faf02bd3b965d")
(setf (get lla2enu::DistanceCalculator :datatype-) "lla2enu/DistanceCalculator")
(setf (get lla2enu::DistanceCalculator :request) lla2enu::DistanceCalculatorRequest)
(setf (get lla2enu::DistanceCalculator :response) lla2enu::DistanceCalculatorResponse)

(defmethod lla2enu::DistanceCalculatorRequest
  (:response () (instance lla2enu::DistanceCalculatorResponse :init)))

(setf (get lla2enu::DistanceCalculatorRequest :md5sum-) "4e22589e822a5a44dc1faf02bd3b965d")
(setf (get lla2enu::DistanceCalculatorRequest :datatype-) "lla2enu/DistanceCalculatorRequest")
(setf (get lla2enu::DistanceCalculatorRequest :definition-)
      "float64 x
float64 y
float64 x_obs
float64 y_obs
---
float64 distance

")

(setf (get lla2enu::DistanceCalculatorResponse :md5sum-) "4e22589e822a5a44dc1faf02bd3b965d")
(setf (get lla2enu::DistanceCalculatorResponse :datatype-) "lla2enu/DistanceCalculatorResponse")
(setf (get lla2enu::DistanceCalculatorResponse :definition-)
      "float64 x
float64 y
float64 x_obs
float64 y_obs
---
float64 distance

")



(provide :lla2enu/DistanceCalculator "4e22589e822a5a44dc1faf02bd3b965d")


