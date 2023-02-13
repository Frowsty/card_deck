from deck import Deck, Card

# Alla tester är skrivna för att testa specifika delar av koden
# Det hör huvudsakligen till att kontrollera om kort har korrekt värde eller klädsel
# men även ifall vi har "hittat" något t.ex duplicates funktionen.
# Att skriva vad alla tester gör känns rätt otrivialt och onödigt då det mesta är "self explanatory"
# Min programmerings filosofi de senaste åren har varit att "Kod ska kommentera sig själv" och en massa extra kommentarer gör allt bara klyddigt
# och oläsligt i mina ögon

# --Hur testen är uppbyggda--
# Vi använder oss av assert men inga try / except block så om ett assert felar av någon anledning så dör programmer där och då
# vilket get oss ett klart tecken på var programmet har gått fel och vad vi kan kolla närmre på. 
# Testen går ut på att kontrollera att våra funktioner ger oss de resultat vi är ute efter vilket är anledningen till att vi kan 
# "hård koda" värden i testerna eftersom vi kan förutse vilka kort är var beroende på vilken funktion som kör
# Test funktionerna är skrivna av mig själv utan hjälp av pytest.


# 2023-02-13: Alla tester gick igenom utan problem

def test_card():
    c = Card(4, "Diamonds")
    assert c.rank == 4
    assert c.suite == "Diamonds"

    print("Passed card test")


def test_deck():
    d = Deck()
    assert len(d) == 55
    print("Passed deck test")

def test_operators():
    c1 = Card(5, "Clubs")
    c2 = Card(6, "Diamonds")
    c3 = Card(5, "Hearts")
    assert c3 == c1
    assert c2 != c1
    assert c1 < c2
    assert c3 == c1
    assert c2 > c3
    assert c3 < c2
    print("Passed operator test")
   
def test_sort():
    d = Deck()
    d.sort()
    assert d.cards[5].rank == 1
    assert d.cards[20].rank == 5
    assert d.cards[52].rank == 13
    print("Passed sort test")

def test_take():
    d = Deck()
    assert d.take().rank == 0
    d.sort()
    assert d.take().rank == 13
    print("Passed take test")

def test_put():
    d = Deck()
    c1 = Card(5, "Clubs")
    c2 = Card(6, "Diamonds")
    c3 = Card(13, "Hearts")
    d.put(c3)
    d.put(c2)
    d.put(c1)
    assert d.take().rank == 5
    assert d.take().rank == 6
    assert d.take().rank == 13

    print("Passed put test")

def test_pick_by_random():
    d = Deck()
    c = d.pick_by_random()
    assert c.rank >= 0
    c = d.pick_by_random()
    assert c.rank >= 0
    print("Passed pick_by_random test")

def test_sort_by_value():
    d = Deck()
    d.sort_by_value()
    c = d.cards[4]
    #assert c.rank == 1
    assert c.suite == "Diamonds"
    c = d.cards[8]
    assert c.rank == 2
    assert c.suite == "Diamonds"
    c = d.cards[20]
    assert c.rank == 5
    assert c.suite == "Diamonds"
    print("Passed sort_by_value test")

def test_sort_by_suit():
    d = Deck()
    d.sort_by_suit()
    c = d.cards[4]
    assert c.suite == "Hearts"
    c = d.cards[16]
    assert c.suite == "Diamonds"
    c = d.cards[30]
    assert c.suite == "Spades"
    print("Passed sort_by_suit test")

def test_remove_jokers():
    d = Deck()
    d.remove_jokers()
    assert d.take().rank != 0
    d = Deck()
    d.sort()
    d.remove_jokers()
    c = d.cards[1]
    assert c.rank != 0
    print("Passed remove_jokers test")

def test_remove_duplicates():
    d = Deck()
    temp = d.remove_duplicates()
    assert len(temp) == 0
    c = Card(1, "Diamonds")
    d.put(c)
    temp = d.remove_duplicates()
    assert len(temp) > 0
    print("Passed remove_duplicates test")

def test_insert():
    temp = list()
    d = Deck()
    d.cards = []
    d2 = Deck()
    d.insert(temp, d2.take())
    d.insert(temp, d2.take())
    d.insert(temp, d2.take())
    d.insert(temp, d2.take())
    d.insert(temp, d2.take())
    d.cards = temp
    assert d.cards[0].rank == 0
    assert d.cards[4].rank == 13
    print("Passed insert test")

def test_deal():
    d = Deck()
    d2 = Deck()
    d.deal(4)
    assert len(d) == 3
    d2.deal(5)
    assert len(d2) == 0
    print("Passed deal test")

if __name__ == '__main__':
    test_card()
    test_deck()
    test_operators()
    test_sort()
    test_take()
    test_put()
    test_pick_by_random()
    test_sort_by_value()
    test_sort_by_suit()
    test_remove_jokers()
    test_remove_duplicates()
    test_insert()
    test_deal()
