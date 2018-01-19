import java.util.Comparator;


public class Table implements Comparable<Table>{
	private int _values[];

	public static final Comparator<Table> MAXCMP = new MaxComparator(); 
	   
	
	
	private static  final class MaxComparator implements Comparator<Table> {
		int compare(Table t1, Table t2) {
			return t1.getMax() - t2.getMax();
		}
	}

	public Table(int size) {
		this._values = new int[size];
	}

	public boolean contains(SelectionPredicate p) {
		for(int i = 0; i < _values.length; ++i) {
			if(p.ok(_values[i])) return true;
		}

		return false;	
	}


	public void setValuePosition(int newVal, int pos) {
		if(pos < _values.length) _values[pos] = newVal;
	}

	public void setAll(int newVal) {
		for(int i = 0; i < _values.length; ++i)
			setValuePosition(newVal, i);
	}

	public int getSum() {
		int sum = 0;
		for(int p: _values)
			sum += p;
		return sum;	
	}

	public int getMax() {
		int max = _values[0];
		for(int el : _values)
			if(el > max)
				max = el;
		return max;
	}

	@Override
	public int compareTo(Table t) {
		return this.getSum() - t.getSum();
	}
}
