(ns neural-networks.perceptron
  (:require [clojure.core.reducers :as reducers]
            [quil.core :as q :include-macros true])
  (:gen-class))

(def width  640)
(def length 360)
(def size   [width length])

(defn activate [number]
  (if (> number 0)
    1
    -1))

(defn perceptron-algorithm [input-list weights-list]
  "The perceptron algorithm as described in \"The Nature of Code\"."
  (activate (reduce + (map * input-list weights-list))))

(defn weights-list? [n weights]
  (and (= n (count weights))
       (map 'and (map 'float? weights))))

(defn random-weights [n]
  (for [i (range 0 n)]
    (- (rand 2) 1)))

(defn perceptron [size learn-rate weights iterations]
  (assert (= size (count weights)))
  {:size       size
   :learn-rate learn-rate
   :weights    weights
   :iterations (+ 1 iterations)})

(defn new-perceptron [size learn-rate]
  (perceptron size learn-rate (random-weights size) 0))

(defn size-of [ptron]
  (get ptron :size))
(defn learn-rate-of [ptron]
  (get ptron :learn-rate))
(defn weights-of [ptron]
  (get ptron :weights))

(defn feed [ptron inputs] ;=> 1 activate, -1 not activate
    (assert (= (size-of ptron) (count inputs)))
    (perceptron-algorithm inputs (weights-of ptron)))

(defn new-weight [learn-rate error weight input]
  (+ weight
     (* learn-rate error input)))

(defn train-once
  [ptron guess inputs desired] ;=> once trained perceptron
  (let [error      (- desired guess)
        learn-rate (learn-rate-of ptron)]
    (perceptron (size-of ptron)
                (learn-rate-of ptron)
                (map (partial new-weight learn-rate error)
                     (weights-of ptron)
                     inputs)
                (get ptron :iterations))))

(defn training-point
  [x y answer] ;=> [inputs desired]
  [[x y 1] answer])

(defn f [x] (+ (* 0.5 x) 1))

;; note outcome is mirrored to usual, downwards for positive ys.
(defn draw-f [width length]
  (q/line 0 (f 0) width (f width)))

(defn f-answer [x y]
  (if (< y (f x))
    -1 1))

(defn f-training-point [width length]
  (let [x (rand width)
        y (rand length)]
    [[x y 1] (f-answer x y)]))

;; ## Quil related definitions

;; ### Drawing and state updating functions

(defn draw-point
  "It draws an empty circle if the ptron does get activated (1) 
  and a filled circle if the ptron doesn't get activated (-1)."
  [ptron training-point guess]
  (let [[[x y bias] _] training-point]
    (if (> guess 0)
      (q/fill 0 0 0)
      (q/fill 255 255 255))
    (q/ellipse x y, 5 5)))

(defn clear-canvas []
  (q/background 255)
  (draw-f width length))

;; We need an atom to hold the global app state.

(def training-state (atom {}))

(defn update-ptron [ptron guess point]
  (let [[inputs answer] point]
    (train-once ptron guess inputs answer)))

(defn update-point
  "Returns a random training point."
  []
  (apply f-training-point size))
  

;; The setup function is only drawn once, before the first frame.

(defn setup []
  (q/frame-rate 200)
  (q/stroke 0)
  (q/stroke-weight 1)
  (clear-canvas)
  (swap! training-state
         assoc
         :ptron (new-perceptron 3 0.00001)
         :t-point (apply f-training-point size)
         :iteration 0
         :count 0))

(defn draw
  "Updates next training-point, and then draws it."
  []
  (let [{:keys [ptron t-point iteration count]}
        @training-state]
    (if (< iteration 2000)
      (let [guess (feed ptron (first t-point))]
        (draw-point ptron t-point guess)
        (let [next-ptron (update-ptron ptron guess t-point)
              next-point (update-point)]
          (swap! training-state 
                 assoc
                 :ptron next-ptron
                 :t-point next-point
                 :iteration (+ 1 iteration))
          (if (= 0 (mod iteration 300))
            (clear-canvas)))))))
 
(defn -main
  [& args]
  ;; Work around dangerous default behaviour in Clojure.
  (alter-var-root #'*read-eval* (constantly false))
  ;; Make quil exit when we close the app.
  (q/sketch
                    :title "A perceptron learning to recognise a line"
                    :settings #(q/smooth 2)
                    :setup setup
                    :draw draw
                    :size [640 360]))
