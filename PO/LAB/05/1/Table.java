public class Table {
	private int _values[];

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
}
