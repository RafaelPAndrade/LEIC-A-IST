public class EqualTo implements SelectionPredicate {
	private int _value;

	public EqualTo(int val) {
		_value = val;
	}

	@Override
	public boolean ok(int i) {
		return i == _value;
	}

}
