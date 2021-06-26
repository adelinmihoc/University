import {Injectable} from '@angular/core';
import {HttpClient, HttpHeaders} from "@angular/common/http";
import {Observable} from "rxjs";
import {Parent} from "./parent.model";
import {map} from "rxjs/operators";
import {Movie} from "./movie.model";
import {Document} from "./document.model";


@Injectable({
  providedIn: 'root'
})
export class ParentService {
  private parentUrl = 'http://localhost/pwExamPractice/2021-php/template/Backend';

  constructor(private httpClient: HttpClient) {
  }

  getAll(): Observable<Parent[]> {
    // const url = `${this.parentUrl}/getVacationDestinations.php`;
    const url = 'http://localhost:8080/api/index.jsp';
    // const url = 'https://localhost:44320/api/VacationDestinations';
    const parents: Observable<Parent[]> = this.httpClient
      .get<Array<Parent>>(url);
    console.log(parents);
    return parents;
  }

  getAllMovies() {
    const url = 'http://localhost:8080/api/filterMovies.jsp';
    const body = JSON.stringify({username: localStorage.getItem('username')});
    let headers = new HttpHeaders();
    headers = headers.append('content-type', 'application/json');
    return this.httpClient.request<Array<Movie>>("POST", url, {
      body: body,
      responseType: 'json',
      observe: 'body'
    });
  }

  getAllDocuments() {
    // const url = 'http://localhost:8080/api/filterDocuments.jsp';
    // const docs: Observable<Document[]> = this.httpClient
    //   .get<Array<Document>>(url);
    // console.log(docs);
    // return docs;
    const url = 'http://localhost:8080/api/filterDocuments.jsp';
    const body = JSON.stringify({username: localStorage.getItem('username')});
    let headers = new HttpHeaders();
    headers = headers.append('content-type', 'application/json');
    return this.httpClient.request<Array<Document>>("POST", url, {
      body: body,
      responseType: 'json',
      observe: 'body'
    });
  }

  filterByName(name: string): Observable<Parent[]> {
    // const url = 'http://localhost:8080/api/filterDestinations.jsp';
    const url = 'https://localhost:44320/api/Filter';
    const body = JSON.stringify({Username: localStorage.getItem('username'), Destination: name});
    let headers = new HttpHeaders();
    headers = headers.append('content-type', 'application/json');
    return this.httpClient.request<Array<Parent>>("POST", url, {
      body: body,
      responseType: 'json',
      observe: 'body'
    });
  }

  save(parent: Parent) {
    console.log(parent);
    return this.httpClient
      .post<Parent>(this.parentUrl, parent, {observe: 'response'});
  }

  delete(parentId: number) {
    const url = `${this.parentUrl}/${parentId}`;
    return this.httpClient.delete(url).subscribe(response => console.log(response));
  }

  getOne(id: number): Observable<Parent> {
    // @ts-ignore
    return this.getAll()
      .pipe(
        map(parents => parents.find(parent => parent.id === id))
      );
  }

  update(parent: Parent) {
    const url = `${this.parentUrl}/${parent.id}`;
    return this.httpClient
      .put<Parent>(url, parent).subscribe(v => console.log(v));
  }

}
