#include <iostream>
#include<boost/histogram.hpp>

using namespace std;
using namespace boost::histogram;
using axes_t = std::vector<axis::regular<>>;

int max_value(const histogram<axes_t>& h) {
    int last_bin = 0;
    for (auto i = h.axis().size()-1; i >= 0; i--) {
        //cout<<" size:"<<i<<endl;
      if (h.at(i) > 0) {
        //cout<<"max-bin: "<<i<<" : "<<h.at(i)<<endl;
        last_bin = i;
        break;
      }
    }
    return last_bin;
}

int min_value(const histogram<axes_t>& h) {
    int first_bin = 0;
    for (auto i = 0; i < h.axis().size(); i++) {
      if (h.at(i) > 0) {
        //cout<<"min-bin: "<<i<<endl;
        first_bin = i;
        break;
      }
    }
    return first_bin;
}

  // we need to check if double is required
int get_bin_value_greater_than_percent(const histogram<axes_t>& h, double percent) {
    // Compute the cumulative sum of bin heights
    double cumsum = 0.0;
    int count = h.axis().size();
    for (auto i = 0; i < count; ++i) {
      cumsum += h.at(i);
    }
    //cout << "Total bin heights: " << cumsum << endl;
    // Find the bin value which is greater than the percentage of all values
    double threshold = percent / 100.0 * cumsum;
    //cout << "threshold: " << threshold << endl;
    int bin_index = 0;
    double sum = 0.0;
    for (auto i = 0; i < h.axis().size(); ++i) {
      sum += h.at(i);
      //cout << "sum: " << sum << endl;
      if (sum >= threshold) {
        bin_index = i;
        //cout<<"bin index : "<<bin_index<<endl;
        break;
      }
    }
    return bin_index;
    
}

int main()
{
    histogram<axes_t> hist;
    //the highest trackable value should be equal to the number of bins for proper calculation of quantile values
    hist = make_histogram(axis::regular<>(10+1, 0, 10+1));
    int init_max_v = max_value(hist);
    cout << "initial max value: " << init_max_v << endl;
    int init_min_v = min_value(hist);
    cout << "initial min value: " << init_min_v << endl;
    hist(4);
    hist(2);
    hist(3);
    hist(4);
    hist(2);
    hist(3);
    hist(8);
    hist(10);
    hist(1);
    hist(9);
    hist(9);
    hist(9);
    hist(7);
    hist(6);
    hist(5);
    hist(11);
    hist(12);
    hist(13);
    hist(14);

    int max_v = max_value(hist);
    int min_v = min_value(hist);

    int count = algorithm::sum(hist);

    int cumsum = 0;
    int count2 = hist.axis().size();
    for (auto i = 0; i < count2; ++i) {
      cumsum += hist.at(i);
    }
    cout << "max value: " << max_v << endl;
    cout << "min hist value: " << min_v << endl;
    cout << "number of elements added: " << count << endl;
    cout << "number of actual elements: " << cumsum << endl;
    cout << "Number of bins: " << hist.axis().size() <<endl;

    cout << "value greater than 10%: " << get_bin_value_greater_than_percent(hist,10)<<endl;
    cout << "value greater than 25%: " << get_bin_value_greater_than_percent(hist,25)<<endl;
    cout << "value greater than 50%: " << get_bin_value_greater_than_percent(hist,50)<<endl;
    cout << "value greater than 75%: " << get_bin_value_greater_than_percent(hist,75)<<endl;
    cout << "value greater than 90%: " << get_bin_value_greater_than_percent(hist,90)<<endl;
    cout << "value greater than 95%: " << get_bin_value_greater_than_percent(hist,95)<<endl;
    cout << "value greater than 99%: " << get_bin_value_greater_than_percent(hist,99)<<endl;
    cout << "value greater than 99.9%: " << get_bin_value_greater_than_percent(hist,99.9)<<endl;
    cout << "value greater than 99.99%: " << get_bin_value_greater_than_percent(hist,99.99)<<endl;
    cout << "value greater than 99.999%: " << get_bin_value_greater_than_percent(hist,99.999)<<endl;
    cout << "value greater than 99.9999%: " << get_bin_value_greater_than_percent(hist,99.9999)<<endl;
    cout << "value greater than 99.99999%: " << get_bin_value_greater_than_percent(hist,99.99999)<<endl;


    histogram<axes_t> snapshot;
    snapshot=hist;
    max_v = max_value(snapshot);
    cout << "Number of copied bins: " << snapshot.axis().size() <<endl;
    cout << "max value: " << max_v << endl;
    snapshot.reset();
    max_v = max_value(snapshot);
    cout << "Number of copied bins: " << snapshot.axis().size() <<endl;
    cout << "max value: " << max_v << endl;
    return 0;
}

/* OUTPUT
initial max value: 0
initial min value: 0
max value: 10
min hist value: 1
number of elements added: 19
number of actual elements: 15
Number of bins: 11
value greater than 10%: 2
value greater than 25%: 3
value greater than 50%: 5
value greater than 75%: 9
value greater than 90%: 9
value greater than 95%: 10
value greater than 99%: 10
value greater than 99.9%: 10
value greater than 99.99%: 10
value greater than 99.999%: 10
value greater than 99.9999%: 10
value greater than 99.99999%: 10
Number of copied bins: 11
max value: 10
Number of copied bins: 11
max value: 0
*/