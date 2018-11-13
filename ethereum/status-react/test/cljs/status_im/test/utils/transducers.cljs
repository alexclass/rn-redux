(ns status-im.test.utils.transducers
  (:require [cljs.test :refer-macros [deftest is testing]]
            [status-im.utils.transducers :as transducers]
            [status-im.native-module.impl.module :as native-module]))

(def ^:private preview-call-1
  {:jail-id 1
   :path [:preview]
   :params {:chat-id 1}
   :callback (fn []
               [[:msg-id 1]])})

(def ^:private preview-call-2
  {:jail-id 1
   :path [:preview]
   :params {:chat-id 1}
   :callback (fn []
               [[:msg-id 2]])})

(def ^:private jail-calls
  '({:jail-id 1
     :path [:suggestions]
     :params {:arg 0}}
    {:jail-id 1
     :path [:function]
     :params {:sub :a}}
    {:jail-id 1
     :path [:function]
     :params {:sub :b}}
    {:jail-id 1
     :path [:suggestions]
     :params {:arg 1}}
    {:jail-id 1
     :path [:suggestions]
     :params {:arg 2}}
    preview-call-1
    preview-call-2))

(deftest last-distinct-by-test
  (testing "Elements are removed from input according to provided `compare-fn`,
           when duplicate elements are removed, the last one stays"
    (is (= (sequence (transducers/last-distinct-by native-module/compare-calls) jail-calls)
           '({:jail-id 1
              :path [:suggestions]
              :params {:arg 2}}
             {:jail-id 1
              :path [:function]
              :params {:sub :a}}
             {:jail-id 1
              :path [:function]
              :params {:sub :b}}
             preview-call-1
             preview-call-2))))
  (testing "Edge cases with input size `N=0` and `N=1` work as well"
    (is (= (sequence (transducers/last-distinct-by identity) '())
           '()))
    (is (= (sequence (transducers/last-distinct-by identity) '(1))
           '(1)))))
