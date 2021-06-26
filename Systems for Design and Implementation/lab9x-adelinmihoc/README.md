
# Lab 9: Angular, Spring, JPA
- work individually; accept the following assignment: https://classroom.github.com/a/1c6tCYRR
- convert the previous project to a web application using Angular
- use Angular version 2 or higher (AngularJS/Angular1 is forbidden)
- use Spring --- xml config forbidden
- use Spring Data JPA (Hibernate) --- xml config forbidden
- log messages using SLF4J
- only one feature is enough, e.g., show list of students
- Spring Boot is (for now) forbidden

# Lab 10: Angular, Spring, JPA
- continue to work individually on the previous project (same repo)
- Spring Boot is, from now on, allowed (the project structure should be the same as before i.e. core, web)
- CRUD operations (the link entity/entities e.g. Rental, StudentDiscipline is/are for now not required; relations - for now, not required)
- Filter, sort operations (client-side and server-side; on server-side, with Spring Data JPA)
- Use both reactive and template-driven forms and validate user input (self study)
- Use ES6 features (or above) and follow redux principles (see readme)
- There should be four root entities and the requirements may be split over them, e.g., CRUD operations on entity1, client-side filters on entity2, server-side filters on entity3 etc

# Lab 11: Angular, Spring, JPA - mapping relationships
- continue to work individually on the previous project (same repo)
- Implement relationships between entities; the fetch type will be eager
- There should be at least four root entities and one repository per root aggregate; there should be no repository for the link entities (e.g. StudentDiscipline); there should be at least one relationship from each of the following: many-to-many, one-to-many, one-to-one (many-to-many may be implemented with two one-to-many associations; one-to-one may be implemented with embeddable)
- Operations on the link entity (e.g. enroll students to disciplines, assign/view/etc grades); reports/statistics

# Lab 12: handling the n + 1 select problem; testing
- continue to work individually on the previous project (same repo)
- all associations must be lazily loaded
- after switching to Lazy fetching, check if the LazyInitializationException actually appears before trying to ‘handle' it (in SpringBoot some settings might be needed in this sense - otherwise everything is fetched eagerly)
- query the entities using: Spring Queries with Named Entity Graphs,  JPQL, Criteria API, Native SQL
- in each repository (e.g: BookRepository, ClientRepository etc) there should be at least two methods using NamedEntityGraphs
- for each repository (e.g: BookRepository, ClientRepository etc), in the corresponding fragment/customized interface, there should be at least two additional methods; these  additional methods should have three different implementations with: JPQL, CriteriaAPI, NativeSql
- in the services only the 'main' repositories should be used (e.g: BookRepository and ClientRepository, not the fragment/customized ones)
- the application should work alternatively with all of the following configurations: EntityGraphs + JPQL, EntityGraphs + CriteriaAPI, EntityGraphs + NativeSql. The configuration switch should be possible by changing annotations or property files, but not java code
- write integration tests for your repositories and services; use DbUnit, xml datasets
- write unit tests for your controllers using Mockito 

# Lab 13-14: Microservices
- The deadline for this lab is week 14; for week 13, there is no deadline, for any lab
- Continue to work individually on the previous project (same repo)
- Refactor the previous project from a monolithic architecture to microservices as shown in the diagram for the CatalogAPP:
- You should provide a similar diagram for your projects
 - At least two services should be implemented in Ruby, the other ones in Java, as seen in the diagram (see readme file for suggested documentation); I have been recently informed that there are some issues in Windows with configuring Rails and Postgres so maybe a Ruby version prior to 3 should be used
 - The services must normally be completely independent (e.g. source control repository, application server, database etc completely independent); for the lab: in your repo, there will be one folder for the entire app and subfolders for each service, i.e., a modular solution (as it was the case until now) should not be attempted; consequently, the current separation in core and web is no longer needed; it is also allowed to have a single db, but each service should interact only with the tables from that business domain (as seen in the diagram)
 - The existing Angular front-end should access the backend via a single entry point (API Gateway) as seen in the diagram; the gateway will forward the requests to the appropriate service/services; it may be implemented either in Java or Ruby (as any other service); the front-end will remain entirely in Angular i.e. Ruby/Rails should only be used in the backend
 - Each service/component from the diagram (including the front-end) will be managed by Docker (i.e. will have its environment defined in its own Dockerfile) and all services/containers will run with Docker Compose; so, practically, with the `docker-compose up` command the entire application will be started
