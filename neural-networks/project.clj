(defproject neural-networks "0.1.0-SNAPSHOT"
  :description "Ioanna's experiment, to get the feel of Clojure and learn some basic ideas about neural networks at the same time. I start with modelling a single perceptron, following http://natureofcode.com/book/chapter-10-neural-networks/"
  :url "https://github.com/ioannad/experiments/neural-networks"
  :license {:name "Eclipse Public License"
            :url "http://www.eclipse.org/legal/epl-v10.html"}
  :dependencies [[org.clojure/clojure "1.8.0"]
                 [quil "2.4.0"]]
  :main ^:skip-aot neural-networks.perceptron
  :target-path "target/%s"
  :profiles {:uberjar {:aot :all}})
