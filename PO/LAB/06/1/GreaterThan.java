public class GreaterThan implements SelectionPredicate {
	private int _value;

	public GreaterThan(int val) {
		_value = val;
	}

	@Override
	public boolean ok(int i) {
		return i > _value;
	}
}
