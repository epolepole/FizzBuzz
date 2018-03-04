import random
from operator import itemgetter

def gen_random_data(initial_year, max_year, number_of_people):
    a_list_of_people = list()
    for person in range(number_of_people):
        birth = random.randint(initial_year, max_year)
        death = random.randint(birth, birth+80)
        a_list_of_people.append([birth, death])
    # print(a_list_of_people)
    return a_list_of_people


def create_birth_death_list(i_list_of_people: list):
    a_birth_death_list = list()
    for person in i_list_of_people:
        a_birth_death_list.append([person[0], 1])
        a_birth_death_list.append([person[1], -1])

    a_birth_death_list = sorted(a_birth_death_list, key=itemgetter(0))
    # print("birth_death_list" + str(a_birth_death_list))
    return a_birth_death_list


def get_lowest_birth(i_list_of_people: list):
    sorted(i_list_of_people, key=itemgetter(0))
    return i_list_of_people[0][0]


def get_highest_death(i_list_of_people: list):
    sorted(i_list_of_people, key=itemgetter(1), reverse=True)
    return i_list_of_people[0][1]


def fast_solution(i_list_of_people):
    max_year = -1
    max_count = -1
    count = 0
    for a_year in range(get_lowest_birth(i_list_of_people), get_highest_death(i_list_of_people) + 1):
        for a_person in i_list_of_people:
            if a_year == a_person[0]:
                count += 1
            elif a_year == a_person[1]:
                count -= 1
            else:
                continue
        if max_count < count:
                max_count = count
                max_year = a_year
    print("max_year: " + str(max_year))
    return max_year


def optimal_solution(i_sorted_birth_deaths):
    count = 0
    max_count = 0
    max_year = 0
    birth_count = 0
    iterations = 1
    number_of_persons = int(len(i_sorted_birth_deaths)/2)
    for date in i_sorted_birth_deaths:
        count += date[1]
        birth_count += 1 if date[1] == 1 else 0
        if max_count < count:
                max_count = count
                max_year = date[0]
        if birth_count == number_of_persons:
            print("stopping at year " + str(date[0]) + " for iteration " + str(iterations))
            break
        iterations += 1
    print("max_year: " + str(max_year))
    return max_year


the_list = gen_random_data(2000, 2100, 1000)
optimal_solution(create_birth_death_list(the_list))
fast_solution(the_list)
