import test2


def test_sum():
    total = test2.sum(4, 5)
    assert total == 9


def test_mul():
    prod = test2.mul(3, 4)
    assert prod == 12